#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>

using namespace std;

const int MAX_STUDENTS = 100;

typedef struct {
    string name;
    string last_name;
    string career;
    int year;
} tStudent;

typedef struct {
    tStudent list_students[MAX_STUDENTS];
    int counter;
} tCourse;

bool operator>(const tStudent &a, const tStudent &b) {
    if (a.career != b.career) return a.career > b.career;
    if (a.year != b.year) return a.year > b.year;
    if (a.last_name != b.last_name) return a.last_name > b.last_name;
    return a.name > b.name;
}

bool operator<(const tStudent &a, const tStudent &b) {
    if (a.career != b.career) return a.career < b.career;
    if (a.year != b.year) return a.year < b.year;
    if (a.last_name != b.last_name) return a.last_name < b.last_name;
    return a.name < b.name;
}

void showMenu();
void loadStudents(tCourse &course);
void enterStudent(tCourse &course);
void showStudents(tCourse &course);
void searchStudent(tCourse &course);
void deleteStudent(tCourse &course);
void order(tCourse &course);
void opcOrder(tCourse &course);
void save(tCourse &course);

int main() {
    showMenu();
    return 0;
}

void showMenu() {
    tCourse course;
    course.counter = 0;

    loadStudents(course);

    int opc;
    do {
        cout << endl;
        cout << "--- MENU de Registro de Alumnos ---" << endl;
        cout << "-----------------------------------" << endl;
        cout << "1- Mostrar Lista de Alumnos" << endl;
        cout << "2- Buscar Alumno" << endl;
        cout << "3- Ingresar Alumno" << endl;
        cout << "4- Eliminar Alumno" << endl;
        cout << "5- Ordenar los Alumnos por Apellido y Nombre" << endl;
        cout << "6- Ordenar los Alumnos por otros campos" << endl;
        cout << "0- Salir" << endl;
        cout << "---------------------------------" << endl;
        cout << "Opcion: ";
        cin >> opc;

        switch (opc) {
            case 1:
                showStudents(course);
                break;
            case 2:
                searchStudent(course);
                break;
            case 3:
                enterStudent(course);
                break;
            case 4:
                deleteStudent(course);
                break;
            case 5:
                order(course);
                break;
            case 6:
                opcOrder(course);
                break;
            case 0:
                save(course);
                cout << "Saliendo del programa..." << endl;
                break;
            default:
                cout << "Opción no válida. Intente nuevamente." << endl;
        }
    } while (opc != 0);
}

void loadStudents(tCourse &course) {
    ifstream archivo("Alumnos.txt");

    if (archivo.is_open()) {
        string line;

        while (getline(archivo, line)) {
            istringstream ss(line);
            string field;

            getline(ss, field, ',');
            course.list_students[course.counter].career = field;

            getline(ss, field, ',');
            if (!field.empty()) {
                course.list_students[course.counter].year = stoi(field);
            } else {
                continue;
            }

            getline(ss, field, ',');
            course.list_students[course.counter].last_name = field;

            getline(ss, field, ',');
            course.list_students[course.counter].name = field;

            course.counter++;
        }
        archivo.close();
    } else {
        cout << "No se pudo abrir el archivo. Se creará uno nuevo." << endl;
    }
}

void enterStudent(tCourse &course) {
    if (course.counter >= MAX_STUDENTS) {
        cout << "No se pueden agregar más alumnos." << endl;
        return;
    }
    tStudent newStudent;

    cout << "---------- INGRESAR Alumno ----------\n";
    cout << "Carrera ";
    cin.ignore();
    getline(cin, newStudent.career);
    cout << "Año: ";
    cin >> newStudent.year;
    cout << "Apellido: ";
    cin >> newStudent.last_name;
    cout << "Nombre: ";
    cin >> newStudent.name;

    course.list_students[course.counter] = newStudent;
    course.counter++;
}

void showStudents(tCourse &course) {
    cout << left << setw(30) << "Carrera"
         << setw(5) << "Año"
         << setw(15) << "Apellido"
         << setw(15) << "Nombre"
         << endl;
    cout << "-------------------------------------" << endl;

    for (int i = 0; i < course.counter; i++) {
        cout << left << setw(30) << course.list_students[i].career
                     << setw(5) << course.list_students[i].year
                     << setw(15) << course.list_students[i].last_name
                     << setw(15) << course.list_students[i].name
                     << endl;
    }
}

void searchStudent(tCourse &course) {
    string last_name, name;
    cout << "------ BUSCAR Alumno ------" << endl;
    cout << "Apellido: ";
    cin >> last_name;
    cout << "Nombre: ";
    cin >> name;
    cout << " --------------------------- " << endl;

    cout << left << setw(30) << "Carrera"
         << setw(5) << "Año"
         << setw(15) << "Apellido"
         << setw(15) << "Nombre"
         << endl;
    cout << "-------------------------------------" << endl;

    bool found = false;
    for (int i = 0; i < course.counter; i++) {
        if (course.list_students[i].last_name == last_name && course.list_students[i].name == name) {
            
        cout << left << setw(30) << course.list_students[i].career
                     << setw(5) << course.list_students[i].year
                     << setw(15) << course.list_students[i].last_name
                     << setw(15) << course.list_students[i].name
                     << endl;
            found = true;
            break;
        }
    }
    if (!found) {
        cout << "Alumno no encontrado." << endl;
    }
}

void deleteStudent(tCourse &course) {
    string last_name, name;
    cout << "------ BUSCAR Alumno ------" << endl;
    cout << "Apellido: ";
    cin >> last_name;
    cout << "Nombre: ";
    cin >> name;

    int index = -1;
    for (int i = 0; i < course.counter; i++) {
        if (course.list_students[i].last_name == last_name && course.list_students[i].name == name) {
            index = i;
            break;
        }
    }
    if (index != -1) {
        for (int i = index; i < course.counter - 1; i++) {
            course.list_students[i] = course.list_students[i + 1];
        }
        course.counter--;
        save(course);
        cout << "Alumno eliminado exitosamente." << endl;
    } else {
        cout << "Alumno no encontrado." << endl;
    }
}

void order(tCourse &course) {
    int opc;
    cout << "--- ORDENAR Alumnos por Apellido y Nombre ---" << endl;
    cout << " 1) Ascendente o 2) Descendente : ";
    cin >> opc;

    if (opc == 1) {
        for (int i = 1; i < course.counter; i++) {

            int pos = i;
            tStudent newStudent;

            while ((pos > 0) && (course.list_students[pos - 1].last_name > course.list_students[pos].last_name)) {

                newStudent = course.list_students[pos];
                course.list_students[pos] = course.list_students[pos - 1];
                course.list_students[pos - 1] = newStudent;
                pos--;
            }
        }
    } else if (opc == 2){

        for (int i = 1; i < course.counter; i++) {
            int pos = i;
            tStudent newStudent;

            while ((pos > 0) && (course.list_students[pos - 1].last_name > course.list_students[pos].last_name)) {
                
                newStudent = course.list_students[pos];
                course.list_students[pos] = course.list_students[pos - 1];
                course.list_students[pos - 1] = newStudent;
                pos--;
                }
            } 
        } else 
                {cout << "La opcion elegida no es valida";}
    showStudents(course);
}

void opcOrder(tCourse &course) {
    int opc;
    cout << "----- OPCIONES de Ordenamiento -----" << endl;
    cout << "Ordenar por: " << endl;
    cout << "1- Carrera" << endl;
    cout << "2- Año" << endl;
    cout << "3- Apellido" << endl;
    cout << "4- Nombre" << endl;
    cout << "Opcion: ";
    cin >> opc;

    switch (opc) {
        case 1:
            for (int i = 1; i < course.counter; i++) {
                tStudent key = course.list_students[i];
                int pos = i - 1;

                while (pos >= 0 && (course.list_students[pos] > key)) {
                    course.list_students[pos + 1] = course.list_students[pos];
                    pos--;
                }
                course.list_students[pos + 1] = key;
            }
            break;

        case 2:
            for (int i = 1; i < course.counter; i++) {
                tStudent key = course.list_students[i];
                int pos = i - 1;

                while ((pos >= 0) && (course.list_students[pos].year > key.year ||
                                   (course.list_students[pos].year == key.year && course.list_students[pos] > key))) {
                    course.list_students[pos + 1] = course.list_students[pos];
                    pos--;
                }
                course.list_students[pos + 1] = key;
            }
            break;

        case 3:
            for (int i = 1; i < course.counter; i++) {
                tStudent key = course.list_students[i];
                int pos = i - 1;

                while (pos >= 0 && (course.list_students[pos].last_name > key.last_name ||
                                   (course.list_students[pos].last_name == key.last_name && course.list_students[pos] > key))) {
                    course.list_students[pos + 1] = course.list_students[pos];
                    pos--;
                }
                course.list_students[pos + 1] = key;
            }
            break;

        case 4:
            for (int i = 1; i < course.counter; i++) {
                tStudent key = course.list_students[i];
                int pos = i - 1;

                while ((pos >= 0) && (course.list_students[pos].name > key.name ||
                                   (course.list_students[pos].name == key.name && course.list_students[pos] > key))) {
                    course.list_students[pos + 1] = course.list_students[pos];
                    pos--;
                }
                course.list_students[pos + 1] = key;
            }
            break;

        default:
            cout << "Opción no válida" << endl;
    }
    showStudents(course);
}

void save(tCourse &course) {
    ofstream archivo("Alumnos.txt");

    for (int i = 0; i < course.counter; i++) {
        archivo << course.list_students[i].career
                << "," << course.list_students[i].year
                << "," << course.list_students[i].last_name
                << "," << course.list_students[i].name
                << endl;
    }
    archivo.close();
}
