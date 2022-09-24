#include <iostream>
using namespace std;
#include "Pais.h"
#include "Ciudad.h"
#include "FileManage.h"

bool puntoA(char* cod) {
    Pais pais;
    FILE* pFile = fopen("paises.dat", "rb");

    if (pFile == NULL) {
        return false;
    }

    while (fread(&pais, sizeof(Pais), 1, pFile)) {
        if (strcmp(pais.getCodigo(), cod) == 0) {
            pais.mostrar();
            return true;
        }
    }

    fclose(pFile);
    return false;
}

void cargarPais(Pais& pais) {
    cout << "Ingrese el codigo del pais: ";
    char cod[4];
    cin >> cod;
    pais.setCodigo(cod);

    cout << "Ingrese el codigo2 del pais: ";
    char cod2[4];
    cin >> cod2;
    pais.setCodigo2(cod2);

    cout << "Ingrese el nombre del pais: ";
    char nombre[35];
    cin >> nombre;
    pais.setNombre(nombre);

    cout << "Ingrese el continente del pais: ";
    char continente[35];
    cin >> continente;
    pais.setContinente(continente);

    cout << "Ingrese la superficie del pais: ";
    float superficie;
    cin >> superficie;
    pais.setSuperficie(superficie);

    cout << "Ingrese la poblacion del pais: ";
    int poblacion;
    cin >> poblacion;
    pais.setPoblacion(poblacion);

    cout << "Ingrese la independencia del pais: ";
    short independencia;
    cin >> independencia;
    pais.setIndependencia(independencia);

    cout << "Ingrese la expectativa de vida del pais: ";
    float expectativa;
    cin >> expectativa;
    pais.setExpectativaDeVida(expectativa);

    cout << "Ingrese el ID de la capital del pais: ";
    int IDCapital;
    cin >> IDCapital;
    pais.setIDCapital(IDCapital);
}

bool puntoB() {

    Pais pais;
    FILE* pFile = fopen("paises.dat", "ab");

    if (pFile == NULL) {
        return false;
    }

    cargarPais(pais);

    bool ok = fwrite(&pais, sizeof(Pais), 1, pFile);

    fclose(pFile);

    return ok;
}

bool punotC() {
    Pais pais;
    FILE* pFile = fopen("paises.dat", "rb");
    if (pFile == NULL) {
        return false;
    }

    while (fread(&pais, sizeof(Pais), 1, pFile)) {
        pais.mostrar();
    }

    fclose(pFile);
    return false;
}

int mostrarCapital(char* cod) {
    Pais pais;
    FILE* pFile = fopen("paises.dat", "rb");
    if (pFile == NULL) {
        return -1;
    }

    while (fread(&pais, sizeof(Pais), 1, pFile)) {
        if (strcmp(pais.getCodigo(), cod) == 0) {
            return pais.getIDCapital();
        }
    }

    fclose(pFile);
    return -1;
}

bool puntoD(char* cod) {
    Ciudad ciudad;
    Ciudad capital;
    FILE* pFile = fopen("ciudades.dat", "rb");

    if (pFile == NULL) {
        return false;
    }

    while (fread(&ciudad, sizeof(Ciudad), 1, pFile)) {
        if (strcmp(ciudad.getIDPais(), cod) == 0) {
            ciudad.mostrar();

            if (ciudad.getID() == mostrarCapital(cod)) {
                capital = ciudad;
            }
        }
    }
    std::cout << "*****************************************" << std::endl;
    std::cout << "La capital es: " << std::endl;
    capital.mostrar();

    fclose(pFile);

    return true;
}

float superficieTotal() {
    Pais pais;
    FILE* pFile = fopen("paises.dat", "rb");
    if (pFile == NULL) {
        return -1;
    }

    float superficie = 0;

    while (fread(&pais, sizeof(Pais), 1, pFile)) {
        superficie += pais.getSuperficie();
    }

    fclose(pFile);
    return superficie;
}

bool puntoE() {
    Pais pais;

    FILE* pFile = fopen("paises.dat", "rb");

    if (pFile == NULL) {
        return false;
    }

    while (fread(&pais, sizeof(Pais), 1, pFile)) {
        std::cout << "Nombre: " << pais.getNombre() << std::endl;
        std::cout << "Superficie: " << pais.getSuperficie() << std::endl;
        std::cout << "Porcentaje: " << (pais.getSuperficie() * 100) / superficieTotal() << "%" << std::endl;
    }

    fclose(pFile);
    return true;
}


template<typename T> void mostrarArchivo(T object, const char* fileName) {
    FILE* pFile = fopen(fileName, "rb");
    if (pFile == NULL) {
        return;
    }

    while (fread(&object, sizeof(T), 1, pFile)) {
        object.mostrar();
    }

    fclose(pFile);
}


int main()
{
    int opcion;

    do
    {
        std::system("cls");
        cout << "1. BUSCAR REGISTRO PAIS POR CODIGO" << endl; // TP 1
        cout << "2. AGREGAR PAIS. VALIDAR QUE NO EXISTA" << endl;
        cout << "3. LISTAR PAISES" << endl;
        cout << "4. LISTAR CUDADES Y POBLACION POR CODIGO PAIS" << endl;
        cout << "5. LISTAR PAISES CON NOMBRE Y SUPERFICIE" << endl;
        cout << "6. PAISES ORDENADO POR POBLACION DECRECIENTE" << endl; // TP 2
        cout << "7. AGREGAR CIUDAD. VALIDAR QUE NO EXISTA" << endl;
        cout << "8. CIUDAD Y POBLACION. QUE POSICION OCUPARIA" << endl;
        cout << "9. GENERAR ARCHHIVO MUNDO. COD PAIS, NOM PAIS, NOMBRE CIUDAD POBLACION MAYOR, POBLACION" << endl;
        cout << "10. OBTENER VECTOR" << endl;
        cout << "11. PAIS POR COD" << endl;
        cout << "0. SALIR" << endl;
        cout << "*********************************************" << endl;
        cout << "Opcion: ";
        cin >> opcion;

        switch (opcion)
        {
        case 1:
            char cod[4];
            std::cout << "ngrese el codigo del pais" << std::endl;
            std::cin >> cod;
            if (!puntoA(cod)) {
                cout << "No se encontro el pais" << endl;
            }
            break;
        case 2:
            if (!puntoB()) {
                cout << "No se pudo agregar el pais" << endl;
            }
            break;
        case 3:
            if (!punotC()) {
                cout << "No se encontro el pais" << endl;
            }
            break;
        case 4:
            char cod2[4];
            std::cout << "ngrese el codigo del pais" << std::endl;
            std::cin >> cod2;
            if (!puntoD(cod2)) {
                cout << "No se pude leer el archivo" << endl;
            }
            break;
        case 5:
            if (!puntoE()) {
                cout << "No se pude leer el archivo" << endl;
            }
            break;
 /*       case 6:
        {
            Pais paises;
			mostrarArchivo(paises, "paises.dat");
			break;
		}
        case 7:
        {
            Ciudad ciudades;
           mostrarArchivo(ciudades, "ciudades.dat");
           break;
        }
        case 8:
        {
            FileManage<Pais> fileManage;
            fileManage.ReadFile("paises.dat");
			break;
        }
             
		case 9:
		{
			FileManage<Ciudad> fileManage;
			fileManage.ReadFile("ciudades.dat");
		}
            break;*/
        case 10:
        {
            FileManage<Pais> fileManage;

            Pais* pais = fileManage.getVector("paises.dat");

            for (int i = 0; i < fileManage.getCantidad("paises.dat"); i++)
            {
                pais[i].mostrar();
            }
        }
            break;
        case 11:
        {
            char cod[3];
            std::cin >> cod;
			
            FileManage<Pais> fileManage;
            Pais pais = fileManage.getObjectByID(cod, "paises.dat");
            pais.mostrar();
        }
            break;
        case 0:
            cout << "Saliendo..." << endl;
            break;
        default:
            cout << "Opcion incorrecta" << endl;
        }
        std::system("pause");

    } while (opcion != 0);

    return 0;
}