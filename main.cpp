#include <iostream>

void redimensionarMatriz(float **&matriz, int &filas, int &columnas);
int main() {
    int filas = 4;  //filas
    int columnas = 5;//columnas
    float **planificación = nullptr;
    planificación = new float*[filas]();
    int **costos_de_producción = nullptr;//el costo por elementos del producto de las 
    costos_de_producción = new int*[columnas]();//cantidad de elementos que se usaran en la produccion
    int opcion = 0;
    for (int i = 0; i < filas; i++) {
        planificación[i] = new float[columnas]();
    }
    for( int i = 0; i < columnas; i++ ) {
        costos_de_producción[i] = new int[filas]();
    }
    int valores[5][4] = {//4 materias primas
        {2, 3, 1, 4}, // Producto 1
        {1, 0, 2, 1}, // Producto 2
        {0, 2, 3, 1}, // Producto 3
        {4, 1, 0, 2}, // Producto 4
        {2, 3, 4, 5}  // Producto 5
    };
    for (int i = 0; i < columnas; i++) {
        for (int j = 0; j < filas; j++) {
            costos_de_producción[i][j] = valores[i][j];
        }
    }
    float *cantidad_materia_prima = nullptr;
    cantidad_materia_prima = new float[4]();//cantidades de materias primas que seran afectadas por costo de produccion
    float *costo_por_unidad = nullptr;
    costo_por_unidad = new float[5]();//costo de los 5 productos estaticos de la planificación

    costo_por_unidad[0]= 10.0;
    costo_por_unidad[1]= 15.0;
    costo_por_unidad[2]= 20.0;
    costo_por_unidad[3]= 25.0;
    costo_por_unidad[4]= 30.0;
    cantidad_materia_prima[0] = 100.0;
    cantidad_materia_prima[1] = 150.0;
    cantidad_materia_prima[2] = 200.0;
    cantidad_materia_prima[3] = 250.0;

    while (opcion != 5) {
        std::cout << "numero de productos: " << columnas << std::endl;
        std::cout << "numero de semanas: " << filas << std::endl;
        std::cout << "------menu principal -------" << std::endl;
        std::cout << "Seleccione una opcion: " << std::endl;
        std::cout << "1. Ver plan de produccion" << std::endl;
        std::cout << "2. Agregar Nueva Semana (Redimensionar Matriz)" << std::endl;
        std::cout << "3. Modificar Producción" << std::endl;
        std::cout << "4. Calcular COGS y Final Inventory" << std::endl;
        std::cout << "5. Salir" << std::endl;
        std::cin >> opcion;
        switch (opcion)
        {
        case 1:
            std::cout<< "Generando planificacion de las "<<filas<<" semanas y "<<columnas<<" productos"<<std::endl;
            for (int i = 0; i < filas; i++) {
                std::cout << "Semana " << i + 1 << ": ";
                for (int j = 0; j < columnas; j++) {
                    std::cout << "producto "<<j+1<<": "<<planificación[i][j] << " ";
                }
                std::cout << std::endl;
            }
            break;
        case 2:
            std::cout << "Redimensionando Matriz..." << std::endl;
            redimensionarMatriz(planificación, filas, columnas);
            break;
        case 3:
            std::cout << "Modificación de producto selecciona 0 para cancelar..." << std::endl;
            std::cout << "Ingrese el numero de semana (1-" << filas << "): ";
            int semanas;
            std::cin >> semanas;
            if(semanas < 1 || semanas > filas) {
                std::cout << "Semana invalida." << std::endl;
            }
            else{
                std::cout << "Ingrese el numero de producto (1-" << columnas << "): ";
                int producto;
                std::cin >> producto;
                if(producto < 1 || producto > columnas) {
                    std::cout << "Producto invalido." << std::endl;
                } else {
                    std::cout << "Ingrese la nueva cantidad producida: ";
                    float nueva_cantidad;
                    std::cin >> nueva_cantidad;
                    planificación[semanas - 1][producto - 1] = nueva_cantidad;
                    std::cout << "Producción actualizada." << std::endl;
                }
            }

            break;
        case 4:
            std::cout << "Calculando COGS y Final Inventory..." << std::endl;
            std::cout << "Ingrese la semana a revisar:" << std::endl;
            std::cin >> semanas;
            if(semanas < 1 || semanas > filas) {
                std::cout << "Semana invalida." << std::endl;
                break;
            }else{
                int produccion_total=0;
                float costo_total=0.0;
                int consumo_de_materia_prima[4] = {0,0,0,0};
                int valor_inventario_final=0;
                for(int j=0;j<columnas;j++){
                    produccion_total+=planificación[semanas-1][j];
                    costo_total+=planificación[semanas-1][j]*costo_por_unidad[j];
                    for(int k=0;k<filas;k++){
                        consumo_de_materia_prima[k]+=planificación[semanas-1][j]*costos_de_producción[j][k];
                    }
                }
                std::cout<<"Produccion total de la semana "<<semanas<<": "<<produccion_total<<std::endl;
                std::cout<<"Costo total de la semana "<<semanas<<": "<<costo_total<<std::endl;
                std::cout<<"Consumo de materia prima de la semana "<<semanas<<": ";
                for(int k=0;k<filas;k++){
                    std::cout<<consumo_de_materia_prima[k]<<" ";
                }
                std::cout<<std::endl;
                break;
            }
        case 5:
            std::cout << "Saliendo y liberando los elementos" << std::endl;
            for (int i = 0; i < filas; i++) {
                delete[] planificación[i];
                delete[] costos_de_producción[i];
            }
            delete[] planificación;
            delete[] costos_de_producción;
            delete[] cantidad_materia_prima;
            delete[] costo_por_unidad;
            break;
        default:
            std::cout << "Opcion no valida" << std::endl;
            break;
        }
    }
}

void redimensionarMatriz(float **&matriz, int &filas, int &columnas) {
    float **aux = new float*[filas + 1]();
    for (int i = 0; i < filas; i++) {
        aux[i] = matriz[i];
    }
    aux[filas] = new float[columnas]();
    delete[] matriz;
    matriz = aux;
    filas++;
}