//IMPORTACION DE ENCABEZADOS
#include <iostream>
#include <C_Arguments.hpp>
//#include <C_Feature.hpp>
#include <C_File.hpp>
#include <C_General.hpp>
#include <C_Image.hpp>
//#include <C_Math.hpp>
#include <C_Matrix.hpp>
#include <C_Memory.hpp>
#include <C_String.hpp>
#include <C_Trace.hpp>

//DEFICIONES PARA COLORES POR PANTALLA
#include <windows.h> 
#define Color SetConsoleTextAttribute(hConsole, K);
#define Celeste K=11;
#define Rojo K=12;
#define Amarillo K=14;
#define Verde K=10;
#define Blanco K=7;

//GESTION DE COLORES POR PANTALLA
	HANDLE  hConsole;
	int K;

//int Test(int argc, char **argv);

/*******************************************
*                                          *
* DECLARACIÓN DE METODOS DE REDIMENSIONADO *
*                                          *
********************************************/

//METODO VECINO MÁS CERCANO
void Redimensionado_Vecino_Cercano(string nombre_Imagen, C_Image imagen, int ImgAncho_Red, int ImgAlto_Red, string red){
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

	cout << "1 # Aplicando Metodo Vecino mas cercano..." << endl;	

	//Imagen de salida
	C_Image imagenSalida(1, ImgAlto_Red, 1, ImgAncho_Red);
	
	//Calcula el alto y ancho de las imagenes
	double x1 = imagen.LastRow() - 1;
	double y1 = imagen.LastCol() - 1;
	double x2 = imagenSalida.LastRow() - 1;
	double y2 = imagenSalida.LastCol() - 1;

	//Calcular la media de las imagenes
	double mediaR = x1 / x2;
	double mediaC = y1 / y2;

	for (int i = 1; i <= ImgAlto_Red; i++){
		for (int j = 1; j <= ImgAncho_Red; j++){
			//Generar salida con el vecino cercano
			imagenSalida(i, j) = imagen(((i - 1)*mediaR) + 1, ((j - 1)*mediaC) + 1);
		}
	}

	//Guardado
	string nombreImagenSalida = "Red_VC_"+red+"_"+nombre_Imagen;
	const char * salida = nombreImagenSalida.c_str();
	imagenSalida.WriteBMP(salida);
	Verde;Color; cout << "Metodo realizado con exito" << endl;
	Blanco;Color;cout << "La imagen se guardo como: "<< nombreImagenSalida << endl;
	cout << " " << endl;
	void Pause();
}

//METODO  BILINEAL
void Redimensionado_Bilineal(string nombre_Imagen, C_Image imagen, int ImgAncho_Red, int ImgAlto_Red, string red){
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

	cout << "2 # Aplicando Metodo Bilineal..." << endl;	

	//Imagen de salida
	C_Image imagenSalida(1, ImgAlto_Red, 1, ImgAncho_Red);
	
	//Calcula el alto y ancho de las imagenes
	double x1 = imagen.LastRow() - 1;
	double y1 = imagen.LastCol() - 1;
	double x2 = imagenSalida.LastRow() - 1;
	double y2 = imagenSalida.LastCol() - 1;
	
	//Calcular la media de las imagenes
	double mediaR = x1 / x2;
	double mediaC = y1 / y2;
	
	int a, b;

	for (int i = 1; i <= ImgAlto_Red; i++){
		for (int j = 1; j <= ImgAncho_Red; j++){
			a = 1;
			b = 1;

			//Comprobar limites
			if (i == ImgAlto_Red){ a = 0; }
			if (j == ImgAncho_Red){ b = 0;}
			
			//Generar salida con los 4 vecinos cercanos
			imagenSalida(i, j) = (	
							imagen(((i - 1)*mediaR) + 1 ,     ((j - 1)*mediaC) + 1) + 
							imagen(((i - 1)*mediaR) + 1 + a , ((j - 1)*mediaC)+ 1) + 
							imagen(((i - 1)*mediaR) + 1 ,     ((j - 1)*mediaC) + 1 + b) + 
							imagen(((i - 1)*mediaR) + 1 + a , ((j - 1)*mediaC) + 1 + b))/4;
		}
	}

	//Guardado
	string nombreImagenSalida = "Red_BL_"+red+"_"+nombre_Imagen;
	const char * salida = nombreImagenSalida.c_str();
	imagenSalida.WriteBMP(salida);
	Verde;Color; cout << "Metodo realizado con exito" << endl;
	Blanco;Color;cout << "La imagen se guardo como: "<< nombreImagenSalida << endl;
	cout << " " << endl;
	void Pause();
};

//METODO  BICUBICO
void Redimensionado_Bicubico(string nombre_Imagen, C_Image imagen, int ImgAncho_Red, int ImgAlto_Red, string red){
    hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

	cout << "3 # Aplicando Metodo Bicubico..." << endl;

	//Imagen de salida
    C_Image imagenSalida(1, ImgAlto_Red, 1, ImgAncho_Red);

	//Calcula el alto y ancho de las imagenes
	double x1 = imagen.LastRow() - 1;
	double x2 = imagenSalida.LastRow() - 1;
	double y1 = imagen.LastCol() - 1;
	double y2 = imagenSalida.LastCol() - 1;
	
	//Calcular la media de las imagenes
	double mediaR = x1 / x2;
	double mediaC = y1 / y2;

	int ax, ay, bx, by, cx, cy, limiteR, limiteC;
	
	for (int i = 1; i <= ImgAlto_Red; i++){
		for (int j = 1; j <= ImgAncho_Red; j++){
			ax = 1;
			ay = 1;
			bx = 2;
			by = 2;
			cx = 3;
			cy = 3;
			limiteR = ((i - 1)*mediaR)+1;
			limiteC = ((j - 1)*mediaC)+1;
			
			//Comprobar limites
			if (i == ImgAlto_Red || limiteR == x1){ax = 0; bx = 0; cx = 0;}
			if (j == ImgAncho_Red || limiteC == y1){ay = 0; by = 0; cy = 0;}
			if (i == ImgAlto_Red-1 || limiteR == x1-1){bx = 0; cx = 0;}
			if (j == ImgAncho_Red-1 || limiteC == y1-1){by = 0; cy = 0;}
			if (i == ImgAlto_Red-2 || limiteR == x1-2){cx = 0;}
			if (j == ImgAncho_Red-2 || limiteC == y1-2){cy = 0;}

			//Generar salida con los 16 vecinos cercanos
			imagenSalida(i, j) = (
								  imagen(((i - 1)*mediaR) + 1,      ((j - 1)*mediaC) + 1) + 
								  imagen(((i - 1)*mediaR) + 1 + ax, ((j - 1)*mediaC) + 1) +
								  imagen(((i - 1)*mediaR) + 1,      ((j - 1)*mediaC) + 1 + ay) + 
								  imagen(((i - 1)*mediaR) + 1 + ax, ((j - 1)*mediaC) + 1 + ay) + 
								  imagen(((i - 1)*mediaR) + 1,      ((j - 1)*mediaC) + by) +
								  imagen(((i - 1)*mediaR) + 1 + ax, ((j - 1)*mediaC) + 1 + by) + 
								  imagen(((i - 1)*mediaR) + 1 + bx, ((j - 1)*mediaC) + 1 + by) + 
								  imagen(((i - 1)*mediaR) + 1 + bx, ((j - 1)*mediaC) + 1 + ay) + 
								  imagen(((i - 1)*mediaR) + 1 + bx, ((j - 1)*mediaC) + 1) + 
								  imagen(((i - 1)*mediaR) + 1 + cx, ((j - 1)*mediaC) + 1) + 
								  imagen(((i - 1)*mediaR) + 1 + cx, ((j - 1)*mediaC) + 1 + ay) + 
								  imagen(((i - 1)*mediaR) + 1,      ((j - 1)*mediaC) + cy) + 
								  imagen(((i - 1)*mediaR) + 1 + cx, ((j - 1)*mediaC) + 1 + by) + 
								  imagen(((i - 1)*mediaR) + 1 + ax, ((j - 1)*mediaC) + 1 + cy) + 
								  imagen(((i - 1)*mediaR) + 1 + bx, ((j - 1)*mediaC) + 1 + cy) + 
								  imagen(((i - 1)*mediaR) + 1 + cx, ((j - 1)*mediaC) + 1 + cy) 
								)/16;
		}
	}
	//Guardado
	string nombreImagenSalida = "Red_BC_"+red+"_"+nombre_Imagen;
	const char * salida = nombreImagenSalida.c_str();
	imagenSalida.WriteBMP(salida);
	Verde;Color; cout << "Metodo realizado con exito" << endl;
	Blanco;Color;cout << "La imagen se guardo como: "<< nombreImagenSalida << endl;
	cout << " " << endl;
	void Pause();
}

//METODOS POR INVESTIGAR Y REALIZAR
//void Redimensionado_Escalera(string nombre_Imagen, C_Image imagen, int ImgAncho, int ImgAlto);
//void Redimensionado_SPline(string nombre_Imagen, C_Image imagen, int ImgAncho, int ImgAlto);
//void Redimensionado_Lanczos(string nombre_Imagen, C_Image imagen, int ImgAncho, int ImgAlto);
//void Redimensionado_Genuine_Fractals(string nombre_Imagen, C_Image imagen, int ImgAncho, int ImgAlto);

/*******************************************
*                                          *
*       PROCESOS EXTRAS DE EJECUCIÓN       *
*                                          *
********************************************/

//METODO CONVERTIR A ESCALA DE GRISES
void Guardar_Gris(string nombre_Imagen, C_Image imagen){
	
	cout <<"Convirtiendo imagen a escala de grises..." <<endl;
	string nombreImagenSalida = "Gris_"+nombre_Imagen;
	const char * salida = nombreImagenSalida.c_str();
	imagen.WriteBMP(salida);
}

/*******************************************
*                                          *
*           EJECUCIÓN PRINCIPAL            *
*                                          *
********************************************/
//Main
int main(){
   
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

	//DECLARACION DE VARIABLES
	int proceso;				//Proceso de redimensionado a realizar
    int anchoImg;				//Ancho de la imagen a procesar
	int altoImg;				//Alto de la imagen a procesar
	int ImgAncho_Red;			//Ancho del resultado de la imagen redimensionada
	int ImgAlto_Red;			//Alto del resultado de la imagen redimensionada
	
	C_Image imagen;				//Imagen a modificar
	
	double redimensionado;		//Tamaño de redimensionado
					
	string nombre_Imagen;		//Nombre de la imagen a cargar
	const char * cadena;        //Nombre de la imagen convertido a cadena

	//PROCESO DE CARGA DE IMAGEN A REDIMENSIONAR
	Celeste;Color;
	cout <<"_____________________________________________________"<< endl;
	cout <<"|                                                   |"<< endl;
	cout <<"|      PRACTICA CON REDIMENSIONADO DE IMAGENES      |"<< endl;
	cout <<"|                                                   |"<< endl;
	cout <<"|                     Alberto Angel Fuentes Funes   |"<< endl;
	cout <<"|___________________________________________________|"<< endl;
	do{
		do{
			Blanco;Color;
			cout << " " << endl;
			cout << "Introduce el nombre de la imagen o (0 para salir): ";
			Amarillo;Color; 
			cin >> nombre_Imagen;
			Blanco;Color;
			if(nombre_Imagen == "0") return 0;
			cadena = nombre_Imagen.c_str();
	
			if (!C_FileExists(cadena)){ //Error 1 --> Si la imagen no ha sido encontrada, vuelve a buscar nueva imagen
				Rojo;Color;
				cout <<"[ERROR][1] La imagen: '"<< cadena <<"' no se ha podido encontrar." <<endl;
				Blanco;Color;
			}

			} while (!C_FileExists(cadena));

		//Lectura de la imagen BMP
		imagen.ReadBMP(cadena);

		//Convertimos la imagen a escala de grises y guardarla, si es necesario.
		imagen.Grey();

		//Comrpobar si ya tenemos la imagen en gris
		string nombreImagenSalida = "Gris_"+nombre_Imagen;
		const char * salida = nombreImagenSalida.c_str();
		if (C_FileExists(salida)) 
			  cout <<"Cargando imagen..." <<endl;
		else {
			Guardar_Gris(nombre_Imagen, imagen);
		}

		//Obtener ancho y alto de la imagen
		anchoImg = imagen.LastCol();
		altoImg = imagen.LastRow();
	
	
		//Obtener el redimensionado
		cout << " " << endl;
		cout << "Introduce el porcentaje de redimensionado: ";
		Amarillo;Color;
		cin >> redimensionado;
		Blanco;Color;
		std::string red = std::to_string(static_cast<long long>(redimensionado));

		redimensionado = redimensionado / 100;			//Calculo del redimensionado
		ImgAncho_Red = anchoImg * redimensionado;		//Calculo del nuevo ancho de la imagen a redimensionar
		ImgAlto_Red = altoImg * redimensionado;			//Calculo del nuevo alto de la imagen a redimensionar
		
		Celeste;Color;
		cout << " " << endl;
		cout << "---------DATOS INTRODUCCIDOS---------"  << endl;Blanco;Color;	  
		cout << "    Su imagen: "<< nombre_Imagen        << endl;  //Salida por pantalla de los datos cargados
		cout << "    Redimensionado: x"<< redimensionado << endl;
		cout << "    Ancho: "<< anchoImg<<" pixeles"     << endl;
		cout << "    Alto: "<< altoImg<<" pixeles"       << endl;Celeste;Color;
		cout << "-------------------------------------"  << endl;

		do{
			cout << " " << endl;
			cout << "-----Introduce un metodo-----"<< endl; Blanco;Color;			
			cout << "1) Metodo Vecino mas cercano" << endl; //Menu de ejecución de metodos
			cout << "2) Metodo Bilineal"           << endl;
			cout << "3) Metodo Bicubico"           << endl;
			cout << "4) Todos los metodos"         << endl;Celeste;Color;
			cout << "-----------------------------"<< endl;Blanco;Color;
			cout << "5) Salir"                     << endl;Celeste;Color;
			cout << "-----------------------------"<< endl;
			Amarillo;Color;
			cin >> proceso;
			Blanco;Color;
		} while (proceso < 0 && proceso >= 10);

		switch (proceso){
			case 1:
				cout << " " << endl;
				Redimensionado_Vecino_Cercano(nombre_Imagen, imagen, ImgAncho_Red, ImgAlto_Red, red);
			break;
			case 2:
				cout << " " << endl;
				Redimensionado_Bilineal(nombre_Imagen, imagen, ImgAncho_Red, ImgAlto_Red, red);
			break;
			case 3:
				cout << " " << endl;	
				Redimensionado_Bicubico(nombre_Imagen, imagen, ImgAncho_Red, ImgAlto_Red, red);
			break;
			case 4:
				cout << " " << endl;
				Celeste;Color;cout << "APLICANDO TODOS LOS METODOS.." << endl;Blanco;Color;	
				Redimensionado_Vecino_Cercano(nombre_Imagen, imagen, ImgAncho_Red, ImgAlto_Red, red);
				Redimensionado_Bilineal(nombre_Imagen, imagen, ImgAncho_Red, ImgAlto_Red, red);
				Redimensionado_Bicubico(nombre_Imagen, imagen, ImgAncho_Red, ImgAlto_Red, red);
			break;
			case 5:
				return 0;
			break;
		};
	
	} while (true); 
	
	return 0;
}

