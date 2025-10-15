#include <iostream>

void redimensionarMatriz(float **&matriz, int &filas, int &columnas);
int main() {
    int filas = 4;  //filas
    int columnas = 5;//columnas
    float **planificación = nullptr;
    planificación = new float*[filas]();
    int opcion = 0;
    for (int i = 0; i < filas; i++) {
        planificación[i] = new float[columnas]();
    }
    int costos_de_producción[5][4] = {//4 materias primas
        {1, 0, 0, 1}, // Producto 1
        {0, 0, 2, 1}, // Producto 2
        {0, 2, 3, 1}, // Producto 3
        {0, 1, 0, 2}, // Producto 4
        {0, 3, 4, 5}  // Producto 5
    };
    float *cantidad_materia_prima = nullptr;
    cantidad_materia_prima = new float[4]();//cantidades de materias primas que seran afectadas por costo de produccion
    float *costo_materia_prima = nullptr;
    costo_materia_prima = new float[4]();
    float *costo_por_unidad = nullptr;
    costo_por_unidad = new float[5]();//costo de los 5 productos estaticos de la planificación

    costo_por_unidad[0]= 10.0;
    costo_por_unidad[1]= 15.0;
    costo_por_unidad[2]= 20.0;
    costo_por_unidad[3]= 25.0;
    costo_por_unidad[4]= 30.0;
    cantidad_materia_prima[0] = 200.0;
    cantidad_materia_prima[1] = 0.0;
    cantidad_materia_prima[2] = 0.0;
    cantidad_materia_prima[3] = 150.0;
    costo_materia_prima[0] = 1.5;
    costo_materia_prima[1] = 3.0;
    costo_materia_prima[2] = 2.0;
    costo_materia_prima[3] = 1.0;

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
            {
            std::cout << "Calculando COGS y Final Inventory..." << std::endl;
            std::cout << "Ingrese la semana a revisar (1-" << filas << "): ";
            std::cin >> semanas;
            
            if(semanas < 1 || semanas > filas) {
                std::cout << "Semana invalida." << std::endl;
                break;
            }
            
            float produccion_total = 0.0;
            float costo_total = 0.0;
            float consumo_de_materia_prima[4] = {0.0, 0.0, 0.0, 0.0};
            for(int j = 0; j < columnas; j++) {
                float unidades = planificación[semanas-1][j];
                produccion_total += unidades;
                costo_total += unidades * costo_por_unidad[j];
                for(int k = 0; k < 4; k++) {
                    consumo_de_materia_prima[k] += unidades * costos_de_producción[j][k];
                }
            }
            float COGS = 0.0;
            for(int k = 0; k < 4; k++) {
                float mp_restante = cantidad_materia_prima[k] - consumo_de_materia_prima[k];
                COGS += mp_restante * costo_materia_prima[k];
            }
            std::cout << "\n--- Reporte de Costos (Semana " << semanas << ") ---" << std::endl;
            std::cout << "Produccion total: " << produccion_total << " unidades" << std::endl;
            std::cout << "Costo Total de Produccion (COGS): $" << costo_total << std::endl;
            std::cout << "Consumo de Materia Prima: ";
            for(int k = 0; k < 4; k++) {
                std::cout << "MP-" << k+1 << " (" << consumo_de_materia_prima[k] << " uni) ";
            }
            std::cout << std::endl;
            std::cout << "Valor del Inventario Final (M.P. restante): $" << COGS << std::endl;
            break;
            }
        case 5:
            std::cout << "Saliendo y liberando los elementos" << std::endl;
            for (int i = 0; i < filas; i++) {
                delete[] planificación[i];
            }
            delete[] planificación;
            delete[] cantidad_materia_prima;
            delete[] costo_por_unidad;
            delete[] costo_materia_prima; 
            break;
        default:
            std::cout << "Opcion no valida" << std::endl;
            break;
        }
    }
}

void redimensionarMatriz(float **&matriz, int &filas, int &columnas) {
    try {
        float **aux = new float*[filas + 1]();
        for (int i = 0; i < filas; i++) {
            aux[i] = matriz[i];
        }
        aux[filas] = new float[columnas]();
        delete[] matriz;
        matriz = aux;
        filas++;
        std::cout << "Matriz redimensionada exitosamente." << std::endl;
    } catch (const std::bad_alloc& e) {
        std::cerr << "Error: No se pudo asignar memoria - " << e.what() << std::endl;
        // No modificar filas ni matriz si falla
    }
}