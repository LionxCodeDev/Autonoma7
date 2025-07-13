#include <iostream>
#include <cstdlib>
#include <cctype>
#include <string>
#include <vector>
#include <iomanip>

using namespace std;

int n;
string productos[100][2];
int precios[100][2];
int ventas[100][7] = {0,0};

void limpiarPantalla() {
    #ifdef _WIN32
        system("cls");  // Windows
    #else
        system("clear"); // Linux/macOS
    #endif
}

void encabezado(){
    // PORTADA DE EL SOFTWARE
    limpiarPantalla();
    cout<<"     ***  ***********************************************  ***"<<endl;
    cout<<"     ***                                                   ***"<<endl;
    cout<<"     ***   GESTION DE INVENTARIOS PARA TIENDAS VIRTUALES   ***"<<endl;
    cout<<"     ***                                                   ***"<<endl;
    cout<<"     ***                                                   ***"<<endl;
    cout<<"     ***          Basado en matrices bidimensionales       ***"<<endl;
    cout<<"     ***                                                   ***"<<endl;
    cout<<"     ***  ***********************************************  ***"<<endl;
    cout<<endl;
}

int validarEnteros(int condi) {
    string entrada;
    int numero;
    bool valido = false;

    //Mientras el bool sea falso o la varaible vacía se repite 
    while (!valido || entrada.empty()){

       cin>>entrada;

        // Validar que no esté vacía y que todos los caracteres sean dígitos
        if (!entrada.empty() && all_of(entrada.begin(), entrada.end(), ::isdigit)) {
            numero = stoi(entrada);
            
            if(condi == -1){
                if (numero >= 0 && numero < 10) {
                    valido = true;
                }
            }
            else{
                if(condi == 1 && numero >= 0 && numero <=7){
                    valido = true;
                }
                else if(condi == 3 && numero <= n){
                    valido = true;
                }
                else if (numero >= 0) {
                    valido = true;
                } 
            }
            
        }
        else{
            //Limpia el cin y evito espacio
            cin.clear();
            if (cin.peek() == '\n') cin.ignore();
        }
       
    }
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    return numero;
}

bool esDigitoOPunto(char c) {
    return isdigit(c) || c == '.';
}

float validarDecimales() {
    string entrada;
    float numero;
    bool valido = false;

    //Mientras el bool sea falso o la varaible vacía se repite 
    while (!valido || entrada.empty()){

        cin>>entrada;

        // Validar que la cadena solo contenga dígitos y como máximo un punto decimal
        int puntos = count(entrada.begin(), entrada.end(), '.');

        bool formatoValido = !entrada.empty() &&
            puntos <= 1 &&
                all_of(entrada.begin(), entrada.end(), esDigitoOPunto);

        if (formatoValido) {
            try {
                numero = stof(entrada);
                if (numero > 0) {
                    valido = true;
                }
            } catch (...) {
                // No hacer nada, simplemente se repetirá el ciclo
            }
        } else {
            cin.clear();
            if (cin.peek() == '\n') cin.ignore();
        }
       
    }

    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    return numero;
}

string validarAlfanumerico() {
    string entrada;
    bool valido = false;

    // Mientras bool sea falso o el dato vacio se repite la condicion
    while (!valido || entrada.empty()){
        
        if (cin.peek() == '\n') cin.ignore();
        getline(cin, entrada);
        
        for (char c : entrada) {
            if (isalnum(c)) {  // si no es letra ni número
                valido = true;
                break;
            }
        }
    } 
    return entrada;
}

string getDay(int dia){
    switch (dia)
    {

    case 0:
    return "Lunes";
    break;

    case 1:
    return "Martes";
    break;

    case 2:
    return "Miercoles";
    break;

    case 3:
    return "Jueves";
    break;

    case 4:
    return "Viernes";
    break;

    case 5:
    return "Sabado";
    break;

    case 6:
    return "Domingo";
    break;
    
    }
}

int getTotalVentas(int producto){
    
    int total = 0;
    
    for(int j = 0; j < 7; j++){
        total = total + ventas[producto][j];
    }

    return total;
}

int getTotalVentasDia(int dia){
    
    int total = 0;
    
    for(int i = 0; i < n; i++){
        total = total + ventas[i][dia];
    }

    return total;
}

void leerProductos(){

    cout<<endl;
    cout<<" --- Ingreso Productos --- "<<endl;
    //For para recorrer el vector y leer los datos uno por uno
    for(int i = 0; i < n; i++){
        
        cout<<"\nNombre ["<<i+1<<"] : ";
        productos[i][0] = validarAlfanumerico();
            
        cout<<"Categoria ["<<i+1<<"] : ";
        productos[i][1] = validarAlfanumerico();    
    
    }

    cout<<endl;
    cout<<endl;
    cout<<" --- Ingreso Precios --- "<<endl;

    for(int i = 0; i < n; i++){
        
        cout<<"\nPrecio de ["<<productos[i][0]<<"] : ";
        precios[i][0] = validarDecimales();
            
        cout<<"Stock ["<<productos[i][0]<<"] : ";
        precios[i][1] = validarEnteros(1);    
    
    }

}

void realizarVenta(int pro, int dia){
    
    int venta;
    cout<<endl;
    
    cout<<"Ingrese la cantidad de la venta: ";
    venta = validarEnteros(0);

    if( venta <= (precios[pro][1] -  getTotalVentas(pro)) ){
        ventas[pro][dia] = venta;
        precios[pro][1] = precios[pro][1] - venta;
        cout<<endl;
        cout<<"Venta realizada con exito"<<endl;
       
    }
    else{
        cout<<endl;
        cout<<"No hay suficientes productos para completar la venta !!"<<endl;
    }

    cout<<endl;
    system("read -p 'Presione enter para continuar ...'"); 
   
}

void seleccionarProducto(int dia){
    
    
    int pro;
    do
    {
        encabezado();
        for(int i = 0; i < n; i++){
            cout<<i+1<<". "<<productos[i][0]<<endl;
        }
        cout<<"0. Atras "<<endl;
        cout<<endl;
        cout<<"Seleccione un producto: ";
        pro = validarEnteros(3);
            
        if(pro == 0){
            break;
        }
        else{
            realizarVenta(pro - 1, dia - 1);
        }
       
    } while (pro != 0);
}

void seleccionarDia(){
    
    int dia;
    
    do
    {
       
        encabezado();
        cout<<"         REALIZAR UNA VENTA      "<<endl;
        cout<<"     ----------------------------      "<<endl;
        cout<<"1. Lunes"<<endl;
        cout<<"2. Martes"<<endl;
        cout<<"3. Miercoles"<<endl;        
        cout<<"4. Jueves"<<endl;
        cout<<"5. Viernes"<<endl;
        cout<<"6. Sabado"<<endl;
        cout<<"7. Domingo"<<endl;
        cout<<"0. Atras"<<endl;
        cout<<endl;
        cout<<"Seleccione un dia: ";
        dia = validarEnteros(1);
       
        if(dia == 0){
            break;
        }
        else{
            seleccionarProducto(dia);
        }
        
    } while (dia != 0);
    
}

void histograma() {
    
    cout << setw(15) << left << "Producto"
     << setw(15) << left << "Categoria"
     << setw(15) << left << "Precio"
     << setw(15) << left << "Stock"<<endl;

    for (int i = 0; i < n; i++) {
        
        if( precios[i][1] > 0 ){
            cout << setw(15) << left << productos[i][0]
                << setw(15) << left << productos[i][1]
                << setw(15) << left << precios[i][0]
                << setw(15) << left << precios[i][1]<<endl;
        }
    }
}

void ingresoTotal(){
    for(int i = 0; i < n; i++){
        int ventas = getTotalVentas(i);
        double total = ventas * precios[i][0];
        cout<<productos[i][0]<<" = "<<total<<endl;
    }
}

int mayor(vector<int> array){
    
    int index = 0;
    
    for (int i = 1; i < array.size(); i++)
    {
        if(array[i] > array[index]){
            index = i;
        }
    }
    return index;
}

void productoMasVendido(){
    
    vector<int> vendidos(n, 0);

    for(int i = 0; i < n; i++){
        vendidos[i] = getTotalVentas(i);
    }

    int index = mayor(vendidos);
    cout<<endl;
    cout<<"El producto "<<productos[index][0]<<" es el mas vendido con "<<vendidos[index]<<endl;
}

void diaMasLucrativo(){
    
    vector<int> vendidos(7, 0);

    for(int i = 0; i < 7; i++){
        vendidos[i] = getTotalVentasDia(i);
    }

    int index = mayor(vendidos);
    cout<<endl;
    cout<<"El dia "<<getDay(index)<<" es el mas lucrativo con "<<vendidos[index]<<endl;
}

void productosAgotados(){
    
    int suma = 0;

    for(int i = 0; i < n; i++){
        if( precios[i][1] == 0 ){
            suma++;
            cout<<productos[i][0]<<endl;
            cout<<endl;
        }
    }

    if(suma == 0){
        cout<<endl;
        cout<<"No hay productos agotados !!"<<endl;
    }

}

void productosBajaRotacion(){

    int total = 0;

    for (int i = 0; i < n; i++)
    {
        int v = getTotalVentas(i);

        if( precios[i][1] > v){
            cout<<productos[i][0]<<" tiene baja rotacion"<<endl;
            total++;
        }
    }
    
    if(total == 0){
        cout<<endl;
        cout<<"No hay productos con baja rotacion !!"<<endl;
    }
}

void descuentoPorCategoria(){

    int total = 0;

    for (int i = 0; i < n; i++)
    {
        if( productos[i][1] == "Agua" ){
            cout<<productos[i][0]<<" aplica el descuento"<<endl;
            total++;
        }
    }
    
    if(total == 0){
        cout<<endl;
        cout<<"No hay productos que apliquen el descuento !!"<<endl;
    }
}

void stockBajo(){

    int total = 0;

    for (int i = 0; i < n; i++)
    {
        if( precios[i][1] < 5 ){
            cout<<productos[i][0]<<" tiene stock bajo "<<endl;
            total++;
        }
    }
    
    if(total == 0){
        cout<<endl;
        cout<<"No hay productos con stock bajo del promedio"<<endl;
    }
}

void opcionesMenu( int opt ){
    switch (opt)
    {
        case 1:
        {
            encabezado();
            cout<<"      VISUALIZACION DE LOS DATOS      "<<endl;
            cout<<"     ----------------------------      "<<endl;
            cout<<endl;
            histograma();
            cout<<endl;
            system("read -p 'Presione enter para continuar ...'");
        }
        break;
        case 2:
        {
            seleccionarDia();
        }
        break;

        case 3: 
        {
            encabezado();
            cout<<"       INGRESO TOTAL POR PRODUCTO      "<<endl;
            cout<<"     ------------------------------      "<<endl;
            ingresoTotal();
            cout<<endl;
            system("read -p 'Presione enter para continuar ...'");
        }
        break;

        case 4:
        {
            encabezado();
            string name;
            cout<<"          PRODUCTO MAS VENDIDO      "<<endl;
            cout<<"     ----------------------------      "<<endl;
            productoMasVendido();
            cout<<endl;
            system("read -p 'Presione enter para continuar ...'");
        }
        break;

        case 5:
        {
            encabezado();
            cout<<"             DIA MAS LUCRATIVO      "<<endl;
            cout<<"     ------------------------------      "<<endl;
            cout<<endl;
            diaMasLucrativo();
            cout<<endl;
            system("read -p 'Presione enter para continuar ...'");
        }
        break;

        case 6:
        {
            encabezado();
            cout<<"           PRODUCTOS AGOTADOS      "<<endl;
            cout<<"     ----------------------------      "<<endl;
            cout<<endl;
            productosAgotados();
            cout<<endl;
            system("read -p 'Presione enter para continuar ...'");
        }
        break;

        case 7:
        {
            encabezado();
            cout<<"          SEGMENTACION DE DATOS      "<<endl;
            cout<<"     ------------------------------      "<<endl;
            productosBajaRotacion();
            cout<<endl;
            system("read -p 'Presione enter para continuar ...'");
        }
        break;

        case 8:
        {
            encabezado();
            cout<<"        DESCUENTO POR CATEGORIA 5%      "<<endl;
            cout<<"     ------------------------------      "<<endl;
            cout<<endl;
            descuentoPorCategoria();
            cout<<endl;
            system("read -p 'Presione enter para continuar ...'");
        }
        break;

         case 9:
        {
            encabezado();
            cout<<"                STOCK BAJO      "<<endl;
            cout<<"     ------------------------------      "<<endl;
            cout<<endl;
            stockBajo();
            cout<<endl;
            system("read -p 'Presione enter para continuar ...'");
        }
        break;
    
        default:
        encabezado();    
        cout<<"GRACIAS POR USAR NUESTRO SISTEMA DE GESTION PARA TIENDAS VIRTUALES :) !"<<endl;
        system("read -p 'Presione enter para continuar ...'");
        break;
    }
}

int validarMenu() {
    string entrada;
    int numero;
    bool valido = false;

    //Mientras el bool sea falso o la varaible vacía se repite 
    while (!valido || entrada.empty()){
        
        encabezado();
        cout<<endl;
        cout<<" 1. Productos disponibles"<<endl;
        cout<<" 2. Realizar una venta"<<endl;
        cout<<" 3. Ingreso total por producto"<<endl;
        cout<<" 4. Producto mas vendido"<<endl;
        cout<<" 5. Dia mas lucrativo"<<endl;
        cout<<" 6. Productos agotados"<<endl;
        cout<<" 7. Productos con baja rotacion"<<endl;
        cout<<" 8. Descuento por categoria (Agua)"<<endl;
        cout<<" 9. Stock bajo"<<endl;
        cout<<" 0. Salir"<<endl;
        cout<<endl;
        cout << "Ingrese una opcion: ";

        cin>>entrada;

        // Validar que no esté vacía y que todos los caracteres sean dígitos
        if (!entrada.empty() && all_of(entrada.begin(), entrada.end(), ::isdigit)) {
            numero = stoi(entrada);
            if (numero >= 0 && numero <= 9) {
                valido = true;
            }
        }
        else{
            //Limpia el cin y evito espacio
            cin.clear();
            if (cin.peek() == '\n') cin.ignore();
        }
    }

    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    return numero;
}

void showMenu(){
    int option;
    //Mientras la opcion no pase la validación o sea diferente de 0 el ciclo se repite
    do
    {
        option = validarMenu();
        opcionesMenu(option);
    } while (option != 0);
    
}

int main() {
    
    //Declaración de variables y vectores
    encabezado();
    cout<<endl;
    cout<<"Ingrese la cantidad de productos: ";
    n = validarEnteros(-1);
    leerProductos();
    showMenu();
    return 0;
}