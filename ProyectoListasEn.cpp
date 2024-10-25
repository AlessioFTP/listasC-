#include <iostream>
#include <cstdlib>
#include <fstream>
#include <sstream>

using namespace std;

void Texto_centrado(string Texto, int y);

void Texto_Ascii (string Texto);

class Lista{
	protected:
		class NodoCursos{
			public:
				string Nombre;
				int Numero;
				NodoCursos* siguiente;
		};
		class NodoEstudiantes{
			public:
				string Nombre, TarjetaIdentidad, CodigoEstudiantil, Curso;
				float Notas[6] = {0, 0, 0, 0, 0, 0};
				int CN;
				NodoEstudiantes* siguiente;
		};
		NodoCursos* RaizCurso;
		NodoEstudiantes* RaizEstudiante;
	public:
		Lista();
		~Lista();
		void IngresarCurso(int _Numero, bool &c);
		void ImprimirCursos();
		void EliminarCurso();
		bool CursoExiste(int _Numero);
		int CantidadCursos();
		int CantidadEstudiantes();
		bool TieneEstudiantes(int _Numero);
		void AgregarEstudiante(string _Nombre, string _TarjetaIdentidad, string _CodigoEstudiantil, string _Curso);
		void ImprimirEstudiantes(int x);
		void EliminarEstudiante();
		void MostrarNotas();
		void AgregarNotas();
		void Promedio();
		void ManejarCuros(int _Numero);
		void ImportarArchivos();
		void ImportarNotas(string _CodigoEstudiantil, float _Notas[6]);
		void GuardarInformacionEstudiantes(fstream& archivo, string nombreCurso);
		void GuardarArchivos();
};

Lista::Lista(){
	RaizCurso = NULL;
	RaizEstudiante = NULL;
}

Lista::~Lista(){
	NodoCursos* recorridoC = RaizCurso;
	NodoCursos* borrarC;
	while (recorridoC != NULL){
		borrarC = recorridoC;
		recorridoC = recorridoC->siguiente;
		delete borrarC;
	}
	NodoEstudiantes* recorridoE = RaizEstudiante;
	NodoEstudiantes* borrarE;
	while (recorridoE != NULL){
		borrarE = recorridoE;
		recorridoE = recorridoE->siguiente;
		delete borrarE;
	}
	RaizEstudiante = NULL;
	RaizCurso = NULL;
	
}

void Lista::IngresarCurso(int _Numero, bool &c){
	bool A = false;
	NodoCursos* nuevo = new NodoCursos();
	string _Nombre;
	if (_Numero == 1){
		_Nombre = "Primero"; 
		A = true;
	}else if (_Numero == 2){
		_Nombre = "Segundo"; 
		A = true;
	}else if (_Numero == 3){
		_Nombre = "Tercero"; 
		A = true;
	}else if (_Numero == 4){
		_Nombre = "Cuarto"; 
		A = true;
	}else if (_Numero == 5){
		_Nombre = "Quinto"; 
		A = true;
	}else if (_Numero == 6){
		_Nombre = "Sexto"; 
		A = true;
	}else if (_Numero == 7){
		_Nombre = "Septimo"; 
		A = true;
	}else if (_Numero == 8){
		_Nombre = "Octavo"; 
		A = true;
	}else if (_Numero == 9){
		_Nombre = "Noveno"; 
		A = true;
	}else if (_Numero == 10){
		_Nombre = "Decimo"; 
		A = true;
	}else if (_Numero == 11){
		_Nombre = "Once"; 
		A = true;
	}
	if (A){
		if (!CursoExiste(_Numero)){
			nuevo->Nombre = _Nombre;
		    nuevo->Numero = _Numero;
		    nuevo->siguiente = NULL;
		    if (RaizCurso == NULL) {
		        RaizCurso = nuevo;
		    } else {
		        NodoCursos* recorrido = RaizCurso;
		        NodoCursos* Auxiliar = NULL;
		        while (recorrido != NULL && (recorrido->Numero < _Numero)){
		            Auxiliar = recorrido;
		            recorrido = recorrido->siguiente;
		        }
		        if (Auxiliar == NULL) {
		            nuevo->siguiente = RaizCurso;
		            RaizCurso = nuevo;
		        } else {
		            Auxiliar->siguiente = nuevo;
		            nuevo->siguiente = recorrido;
		        }
		    }
		}else{
			Texto_centrado("Solo se puede crear un curso una sola vez.", 1);
			c = false;
			}
	}else Texto_centrado("Solo se puede ingresar cursos desde primiero (1) hasta once (11).", 1);
}

void Lista::ImprimirCursos(){
	NodoCursos* recorrido = RaizCurso;
	int i = 1;
	cout << endl;
	Texto_centrado("Cursos: ", 1);
	while(recorrido!=NULL){
		string Mensaje = "\t\t\t\t\t\t     " + to_string(i++) + ". " + recorrido->Nombre;
		cout << Mensaje << endl;
		recorrido=recorrido->siguiente;
	}
}

void Lista::EliminarCurso(){
	int _Numero;
	Texto_centrado("Ingrese el numero del curso a borrar: ", 0);
	cin >> _Numero;
    if (RaizCurso == NULL) {
        Texto_centrado("La lista de cursos está vacía", 1);
        return;
    }
	NodoCursos* recorrido = RaizCurso;
	if (recorrido->Numero == _Numero){
		string Mensaje = "El curso " + RaizCurso->Nombre + " ha sido borrado con exito."; 
		Texto_centrado(Mensaje,1);
		RaizCurso = recorrido->siguiente;
		delete recorrido; 
	}else{
		while (recorrido->siguiente != NULL && recorrido->siguiente->Numero != _Numero){
			recorrido = recorrido->siguiente;
		}
		if (recorrido->siguiente != NULL && recorrido->siguiente->Numero == _Numero){
			NodoCursos* Borrar = recorrido->siguiente;
			recorrido->siguiente = Borrar->siguiente;
			string Mensaje = "El curso " + Borrar->Nombre + " ha sido borrado con exito."; 
			Texto_centrado(Mensaje,1);
			delete Borrar;
		}else{
			Texto_centrado("Curso No encontrado", 1);
		}
	}
}

bool Lista::CursoExiste(int _Numero){
	NodoCursos* recorrido = RaizCurso;
	while (recorrido != NULL && (recorrido->Numero != _Numero)){
		recorrido = recorrido->siguiente;
	}
	if (recorrido != NULL)
		return true;
	else
		return false;
}

int Lista::CantidadCursos(){
	NodoCursos* recorrido = RaizCurso;
	int i = 0;
	while(recorrido!=NULL){
		i++;
		recorrido=recorrido->siguiente;
	}
	return i;
}

int Lista::CantidadEstudiantes(){
	int i = 0;
	NodoEstudiantes* aux = RaizEstudiante;
	while (aux != NULL){
		i++;
		aux = aux->siguiente;
	}
	return i;
}

bool Lista::TieneEstudiantes(int _Numero){
	NodoEstudiantes* recorrido = RaizEstudiante;
		while(recorrido!=NULL){
			if (recorrido->CN == _Numero)
				return true;
			recorrido=recorrido->siguiente;
		}
		return false;
}

void Lista::AgregarEstudiante(string _Nombre, string _TarjetaIdentidad, string _CodigoEstudiantil, string _Curso){
	NodoEstudiantes* nuevo = new NodoEstudiantes;
	nuevo->Nombre = _Nombre;
	nuevo->TarjetaIdentidad = _TarjetaIdentidad;
	nuevo->CodigoEstudiantil = _CodigoEstudiantil;
	nuevo->Curso = _Curso;
	nuevo->siguiente = NULL;
	string Auxiliar;
	for (int i = 0; i < 3; i++){
		Auxiliar += _Curso[i];
	}
	if (Auxiliar == "Pri"){
		nuevo->CN = 1;}
	else if (Auxiliar == "Seg"){
		nuevo->CN = 2;}
	else if (Auxiliar == "Ter"){
		nuevo->CN = 3;}
	else if (Auxiliar == "Cua"){
		nuevo->CN = 4;}
	else if (Auxiliar == "Qui"){
		nuevo->CN = 5;}
	else if (Auxiliar == "Sex"){
		nuevo->CN = 6;}
	else if (Auxiliar == "Sep"){
		nuevo->CN = 7;}
	else if (Auxiliar == "Oct"){
		nuevo->CN = 8;}
	else if (Auxiliar == "Nov"){
		nuevo->CN = 9;}
	else if (Auxiliar == "Dec"){
		nuevo->CN = 10;}
	else if (Auxiliar == "Onc"){
		nuevo->CN = 11;}
	if(CantidadEstudiantes() == 0){
		RaizEstudiante = nuevo;
	}else{
		NodoEstudiantes* recorrido = RaizEstudiante;
		NodoEstudiantes* Aux = NULL;
		while (recorrido != NULL && (recorrido->CN < nuevo->CN)){
			Aux = recorrido;
			recorrido = recorrido->siguiente;
		}
		if (Aux == NULL){
			nuevo->siguiente = RaizEstudiante;
			RaizEstudiante = nuevo;
		}else{
            Aux->siguiente = nuevo;
            nuevo->siguiente = recorrido;
		}
	}
}

void Lista::ImprimirEstudiantes(int x){
	NodoEstudiantes* recorrido = RaizEstudiante;
	int i = 1;
	cout << endl;
	if (x == 0){
	Texto_centrado("Hay "+ to_string(CantidadEstudiantes()) + " estudiantes, los cuales son: ", 1);
		while(recorrido!=NULL){
			string Mensaje = to_string(i++) + ". " + "Nombre: " + recorrido->Nombre + " CodigoEstudiantil: " + recorrido->CodigoEstudiantil + " Curso: " + recorrido->Curso;
			Texto_centrado(Mensaje, 1);
			recorrido=recorrido->siguiente;
		}
	}else{	
		while(recorrido!=NULL){
			if (recorrido->CN == x){
				string Mensaje = to_string(i++) + ". " + "Nombre: " + recorrido->Nombre + " CodigoEstudiantil: " + recorrido->CodigoEstudiantil + " Curso: " + recorrido->Curso;
				Texto_centrado(Mensaje, 1);
			}
			recorrido=recorrido->siguiente;
		}
	}
}

void Lista::EliminarEstudiante(){
	string _CodigoEstudiantil;
	Texto_centrado("Ingrese el código estudiantil del estudiante a borrar: ", 0);
	cin.ignore();
	getline(cin, _CodigoEstudiantil);
	NodoEstudiantes* recorrido = RaizEstudiante;
	if (recorrido->CodigoEstudiantil == _CodigoEstudiantil){
		string Mensaje = "El estudainte " + RaizEstudiante->Nombre + " ha sido borrado con exito."; 
		Texto_centrado(Mensaje,1);
		RaizEstudiante = recorrido->siguiente;
		delete recorrido; 
	}else{
		while (recorrido->siguiente != NULL && recorrido->siguiente->CodigoEstudiantil != _CodigoEstudiantil){
			recorrido = recorrido->siguiente;
		}
		if (recorrido->siguiente != NULL && recorrido->siguiente->CodigoEstudiantil == _CodigoEstudiantil){
			NodoEstudiantes* Borrar = recorrido->siguiente;
			NodoEstudiantes* Proximo = Borrar->siguiente;
			recorrido->siguiente = Proximo;
			string Mensaje = "El estudiante " + Borrar->Nombre + " ha sido borrado con exito."; 
			Texto_centrado(Mensaje,1);
			delete Borrar;
		}else{
			Texto_centrado("Estudiante no encontrado.", 1);
		}
	}
}

void Lista::MostrarNotas(){
	string _CodigoEstudiantil;
	Texto_centrado("Ingrese el código estudiantil del estudiante que desea ver las notas: ", 0);
	cin.ignore();
	getline(cin, _CodigoEstudiantil);
	NodoEstudiantes* recorrido = RaizEstudiante;
	while (recorrido != NULL && recorrido->CodigoEstudiantil !=_CodigoEstudiantil){
		recorrido = recorrido->siguiente;
	}
	if (recorrido != NULL){
		cout << endl;
		string Mensaje = "Las notas de " + recorrido->Nombre + " son: ";
		for (int i = 0; i < 6; i++){
			if (i != 5)
			Mensaje += to_string(recorrido->Notas[i]) + ", ";
			else Mensaje += to_string(recorrido->Notas[i]) + ".";
		}
		Texto_centrado(Mensaje, 1);
	}else Texto_centrado("Estudiante no encontrado.", 1);
}

void Lista::AgregarNotas(){
	string _CodigoEstudiantil;
	Texto_centrado("Ingrese el código estudiantil del estudiante que desea modificar las notas: ", 0);
	cin.ignore();
	getline(cin, _CodigoEstudiantil);
	NodoEstudiantes* recorrido = RaizEstudiante;
	while (recorrido != NULL && recorrido->CodigoEstudiantil !=_CodigoEstudiantil){
		recorrido = recorrido->siguiente;
	}
	if (recorrido != NULL){
		cout << endl;
		Texto_centrado("Las notas de " + recorrido->Nombre + " son: ",1);
		for (int i = 0; i < 6; i++){
			Texto_centrado(to_string(i + 1 ) + ". " + to_string(recorrido->Notas[i]), 1);
		}
		short int op;
		float Nota;
		Texto_centrado("Ingrese el indice de la nota que desea modificar (0 si desea modificar todas): ", 0);
		cin >> op;
		switch (op){
			case 0:{
				for (int i = 0; i < 6; i++){
					Texto_centrado("Ingrese la nota #" + to_string(i + 1) + ": ", 0);
					cin >> Nota;
					recorrido->Notas[i] = Nota;
				}
				Texto_centrado("Notas Modificada con exito.", 1);
				break;
			}
			case 1:{
				Texto_centrado("Ingrese la nota #1: " , 0);
				cin >> Nota;
				recorrido->Notas[0] = Nota;
				Texto_centrado("Nota Modificada con exito.", 1);
				break;
			}
			case 2:{
				Texto_centrado("Ingrese la nota #2: " , 0);
				cin >> Nota;
				recorrido->Notas[1] = Nota;
				Texto_centrado("Nota Modificada con exito.", 1);
				break;
			}
			case 3:{
				Texto_centrado("Ingrese la nota #3: " , 0);
				cin >> Nota;
				recorrido->Notas[2] = Nota;
				Texto_centrado("Nota Modificada con exito.", 1);
				break;
			}
			case 4:{
				Texto_centrado("Ingrese la nota #4: " , 0);
				cin >> Nota;
				recorrido->Notas[3] = Nota;
				Texto_centrado("Nota Modificada con exito.", 1);
				break;
			}
			case 5:{
				Texto_centrado("Ingrese la nota #5: " , 0);
				cin >> Nota;
				recorrido->Notas[4] = Nota;
				Texto_centrado("Nota Modificada con exito.", 1);
				break;
			}
			case 6:{
				Texto_centrado("Ingrese la nota #6: " , 0);
				cin >> Nota;
				recorrido->Notas[5] = Nota;
				Texto_centrado("Nota Modificada con exito.", 1);
				break;
			}
			default:{
				Texto_centrado("Indice no valido.", 1);
				system ("Pause");
				system ("cls");
				break;
			}	
		}
	}else Texto_centrado("Estudiante no encontrado.", 1);
}

void Lista::Promedio(){
	string _CodigoEstudiantil;
	Texto_centrado("Ingrese el código estudiantil del estudiante que desea ver el promedio: ", 0);
	cin.ignore();
	getline(cin, _CodigoEstudiantil);
	NodoEstudiantes* recorrido = RaizEstudiante;
	while (recorrido != NULL && recorrido->CodigoEstudiantil !=_CodigoEstudiantil){
		recorrido = recorrido->siguiente;
	}
	if (recorrido != NULL){
		cout << endl;
		string Mensaje = "Las notas de " + recorrido->Nombre + " son: ";
		float Promedio = 0;
		for (int i = 0; i < 6; i++){
			if (i != 5)
			Mensaje += to_string(recorrido->Notas[i]) + ", ";
			else Mensaje += to_string(recorrido->Notas[i]) + ".";
			Promedio += recorrido->Notas[i];
		}
		Promedio /= 6;
		Texto_centrado(Mensaje, 1);
		Texto_centrado("El promedio del estudiante " + recorrido->Nombre + " es de: " + to_string(Promedio), 1);
	}else Texto_centrado("Estudiante no encontrado.", 1);
	
}

void Lista::ManejarCuros(int _Numero){	
	NodoCursos* recorrido = RaizCurso;
	while ((recorrido->Numero != _Numero) && recorrido != NULL){
	recorrido = recorrido->siguiente;
	}
	short int op;
	do{
		Texto_Ascii("Curso " + recorrido->Nombre);
		Texto_centrado("-----------------------Menú-----------------------",1 );
		Texto_centrado("Digite una opción.", 1);
		Texto_centrado("0. Salir", 1);
		Texto_centrado("1. Agregar un estudiante al curso " + recorrido->Nombre , 1);
		Texto_centrado("2. Imprimir los estudiantes del curso " + recorrido->Nombre, 1);
		Texto_centrado("3. Eliminar un estudiante del curso " + recorrido->Nombre, 1);
		Texto_centrado("4. Ver las notas de un estudiante de " + recorrido->Nombre, 1);
		Texto_centrado("5. Agregarle notas a un estudiante de " + recorrido->Nombre, 1);
		Texto_centrado("6. Conocer el promedio de un estudiante de " + recorrido->Nombre, 1);
		Texto_centrado("Ingrese la opción: ", 0);
		cin >> op;
		switch (op){
			case 0:{
				break;
			}
			case 1:{
				string Nombre, TarjetaIdentidad, CodigoEstudiantil;
				Texto_centrado("Ingrese el nombre del estudiante: ", 0);
				cin.ignore();
				getline(cin, Nombre);
				Texto_centrado("Ingrese la tarjeta de identidad del estudiante: ", 0);
				getline(cin, TarjetaIdentidad);
				Texto_centrado("Ingrese el código estudiantil del estudiante: ", 0);
				getline(cin, CodigoEstudiantil);
				AgregarEstudiante(Nombre, TarjetaIdentidad, CodigoEstudiantil, recorrido->Nombre);
				Texto_centrado("El estudiante " + Nombre + " ha sido agregado con exito al curso " + recorrido->Nombre, 1);
				system ("Pause");
				system ("cls");
				break;
			}
			case 2:{
				if(TieneEstudiantes(_Numero)){
					Texto_centrado("En el curso " + recorrido->Nombre + " hay los siguientes estudiantes: ", 1);
					ImprimirEstudiantes(recorrido->Numero);
				}else Texto_centrado("El curso " + recorrido->Nombre + " no posee ningun estudiante.", 1);
				system ("Pause");
				system ("cls");
				break;
			}
			case 3:{
				if(TieneEstudiantes(_Numero)){
					Texto_centrado("En el curso " + recorrido->Nombre + " hay los siguientes estudiantes: ", 1);
					ImprimirEstudiantes(recorrido->Numero);
					EliminarEstudiante();
				}else Texto_centrado("El curso " + recorrido->Nombre + " no posee ningun estudiante para poder eliminar.", 1);
				system ("Pause");
				system ("cls");
				break;
			}
			case 4:{
				if(TieneEstudiantes(_Numero)){
					Texto_centrado("En el curso " + recorrido->Nombre + " hay los siguientes estudiantes: ", 1);
					ImprimirEstudiantes(recorrido->Numero);
					MostrarNotas();
				}else Texto_centrado("El curso " + recorrido->Nombre + " no posee ningun estudiante para poder ver las notas.", 1);
				system ("Pause");
				system ("cls");
				break;
			}
			case 5:{
				if(TieneEstudiantes(_Numero)){
					Texto_centrado("En el curso " + recorrido->Nombre + " hay los siguientes estudiantes: ", 1);
					ImprimirEstudiantes(recorrido->Numero);
					AgregarNotas();
				}else Texto_centrado("El curso " + recorrido->Nombre + " no posee ningun estudiante para poder modificar las notas.", 1);
				system ("Pause");
				system ("cls");
				break;
			}
			case 6:{
				if(TieneEstudiantes(_Numero)){
					Texto_centrado("En el curso " + recorrido->Nombre + " hay los siguientes estudiantes: ", 1);
					ImprimirEstudiantes(recorrido->Numero);
					Promedio();
				}else Texto_centrado("El curso " + recorrido->Nombre + " no posee ningun estudiante para poder ver su promedio.", 1);
				system ("Pause");
				system ("cls");
				break;
			}
			default:{
				Texto_centrado("Opción incorrecta, ingrese una opción valida", 1);
				system ("Pause");
				system ("cls");
				break;
			}
		}
	}while (op != 0);
}

void Lista::ImportarNotas(string _CodigoEstudiantil, float _Notas[6]){
	NodoEstudiantes* recorrido = RaizEstudiante;
	while (recorrido != NULL && recorrido->CodigoEstudiantil !=_CodigoEstudiantil){
		recorrido = recorrido->siguiente;
	}
	for (int i = 0; i < 6; i++){
		recorrido->Notas[i] = _Notas[i];
	}
}

void Lista::ImportarArchivos(){
    fstream Cursos("Cursos.csv", ios::in);
    int i = 0;
    if (!Cursos.is_open()) {
        fstream CrearCSV("Cursos.csv", ios::out);
        CrearCSV.close();
    }else{
        string linea;
        getline(Cursos, linea);
        int x[11];
        stringstream Linea(linea);
        string aux;
        while (getline(Linea, aux, ';')) {
            x[i++] = stoi(aux);
        }
         for (int j = 0; j < i; j++) {
         	bool c = true;
            IngresarCurso(x[j], c);
        }
        Cursos.close();
	    NodoCursos* recorrido = RaizCurso;
	    for(int j = 0; j < i; j++){
	    	string NombreCSV = recorrido->Nombre + ".csv";
	    	fstream Curso(NombreCSV, ios::in);
			string linea;
			getline(Curso, linea);
			while(getline(Curso, linea)){
				string _Nombre, _CodigoEstudiantil, _TarjetaIdentidad, Nota1, Nota2, Nota3, Nota4, Nota5, Nota6;
				float _Notas[6];
				stringstream Linea (linea);
				getline(Linea, _Nombre, ';');
				getline(Linea, _CodigoEstudiantil, ';');
				getline(Linea, _TarjetaIdentidad, ';');
				getline(Linea, Nota1, ';');
				getline(Linea, Nota2, ';');
				getline(Linea, Nota3, ';');
				getline(Linea, Nota4, ';');
				getline(Linea, Nota5, ';');
				getline(Linea, Nota6, ';');
				_Notas[0] = stof(Nota1);
				_Notas[1] = stof(Nota2);
				_Notas[2] = stof(Nota3);
				_Notas[3] = stof(Nota4);
				_Notas[4] = stof(Nota5);
				_Notas[5] = stof(Nota6);
				AgregarEstudiante(_Nombre, _TarjetaIdentidad, _CodigoEstudiantil, recorrido->Nombre);
				ImportarNotas(_CodigoEstudiantil, _Notas);
			}
			recorrido = recorrido->siguiente;
		}
    }
    
}

void Lista::GuardarArchivos(){
	fstream Cursos("Cursos.csv", ios::out);
	NodoCursos* recorridoCursos = RaizCurso;
	while (recorridoCursos != NULL){
		Cursos << to_string(recorridoCursos->Numero) + ";";
		recorridoCursos = recorridoCursos->siguiente;
	}
	Cursos.close();
	NodoCursos* recorridoGuardado = RaizCurso;
	while (recorridoGuardado != NULL){
		string NombreCSV = recorridoGuardado->Nombre + ".csv";
		fstream Curso (NombreCSV, ios::out);
		Curso << "Nombre;CodigoEstudiantil;TarjetaIdentidad;Nota1;Nota2;Nota3;Nota4;Nota5;Nota6" << endl;
		GuardarInformacionEstudiantes(Curso, recorridoGuardado->Nombre);
		Curso.close();
		recorridoGuardado = recorridoGuardado->siguiente;
	}
}

void Lista::GuardarInformacionEstudiantes(fstream& archivo, string nombreCurso){
    NodoEstudiantes* recorridoEstudiante = RaizEstudiante;
    while (recorridoEstudiante != NULL) {
    	if (recorridoEstudiante->Curso == nombreCurso){
        archivo << recorridoEstudiante->Nombre << ";"
                << recorridoEstudiante->CodigoEstudiantil << ";"
                << recorridoEstudiante->TarjetaIdentidad << ";"
                << to_string(recorridoEstudiante->Notas[0]) << ";"
                << to_string(recorridoEstudiante->Notas[1]) << ";"
                << to_string(recorridoEstudiante->Notas[2]) << ";"
                << to_string(recorridoEstudiante->Notas[3]) << ";"
                << to_string(recorridoEstudiante->Notas[4]) << ";"
                << to_string(recorridoEstudiante->Notas[5]) << endl;
            }
        recorridoEstudiante = recorridoEstudiante->siguiente;
    }
}

class Manejo{
	public:
		Manejo(){
		}
		void GestionarCursos(Lista &Colegio);
		void GestionarCursoEspe(Lista &Colegio);
};

void Manejo::GestionarCursos(Lista &Colegio){
	short op;
	do{
		Texto_Ascii("Cursos");
		Texto_centrado("-----------------------Menú-----------------------",1 );
		Texto_centrado("Digite una opción.", 1);
		Texto_centrado("0. Salir", 1);
		Texto_centrado("1. Imprimir los cursos", 1)	;
		Texto_centrado("2. Agregar un nuevo curso", 1);
		Texto_centrado("3. Eliminar un curso", 1);
		Texto_centrado("Ingrese la opción: ", 0);
		cin >> op;
		switch (op){
			case 0:{
				break;
			}
			case 1:{
				if (Colegio.CantidadCursos() > 0)
					Colegio.ImprimirCursos();
				else Texto_centrado ("No hay cursos para mostrar", 1);
				system ("Pause");
				system ("cls");
				break;
			}
			case 2:{
				int x;
				string l;
				Texto_centrado("Ingrese el numero del curso a crear: ", 0);
				cin >> x;
				bool c = true;
				Colegio.IngresarCurso(x, c);
				if (Colegio.CursoExiste(x) && c){
					Texto_centrado("Curso agregado con exito", 1);
				}
				system ("Pause");
				system ("cls");
				break;
			}
			case 3:{
				if (Colegio.CantidadCursos() > 0){
					Colegio.ImprimirCursos();
					Colegio.EliminarCurso();
				}
				else Texto_centrado ("No hay cursos para eliminar", 1);
				system ("Pause");
				system ("cls");
				break;
			}
			default:{
				Texto_centrado("Opción incorrecta, ingrese una opción valida", 1);
				system ("Pause");
				system ("cls");
				break;
			}
		}
	}while(op != 0);
}

void Manejo::GestionarCursoEspe(Lista &Colegio){
	Texto_Ascii("Cursos");
	cout << endl;
	if (Colegio.CantidadCursos() > 0){
		int _Numero;
		Colegio.ImprimirCursos();
		Texto_centrado("Ingrese el numero curso que desea gestionar, no el indice que se muestra: ", 0);
		cin >> _Numero;
		if (Colegio.CursoExiste(_Numero)){
			system ("cls");
			Colegio.ManejarCuros(_Numero);
		}else{
			Texto_centrado("El curso no exitste. ", 1);
		}
	}else Texto_centrado("La lista de cursos está vacía.", 1);
}

void Menu(Manejo Administracion, Lista &Colegio);

int main(){
	Lista Colegio;
	Colegio.ImportarArchivos();
	setlocale(LC_ALL, "spanish");
	Manejo Administracion;
	Menu(Administracion, Colegio);
	return 0;
}

void Menu(Manejo Administracion, Lista &Colegio){
	short int op;
	do{
		Texto_Ascii("Colegio La2bleA");
		Texto_centrado("-----------------------Menú-----------------------",1 );
		Texto_centrado("Digite una opción.", 1);
		Texto_centrado("0. Cerrar el programa.", 1);
		Texto_centrado("1. Gestionar los cursos.", 1);
		Texto_centrado("2. Gestionar un curso en especifico.", 1);
		Texto_centrado("3. Imprimir todos los estudiantes del colegio.", 1);
		Texto_centrado("4. Guardar los cambios hechos.", 1);
		Texto_centrado("Ingrese la opción: ", 0);
		cin >> op;
		switch (op){
			case 0:{
					short int opc;
				do{
					Texto_centrado("¿Desea guardar los cambios realizados?, digite 1 sí desea guardar, o 2 sí no: ", 0);
					cin >> opc;
					switch (opc){
						case 1:{						
							Colegio.GuardarArchivos();
							Texto_centrado("Archivos guardados con exito.", 1);
							break;
						}
						case 2:{
							break;
						}
						default:{
							Texto_centrado("Opción incorrecta, ingrese una opción valida", 1);
							break;
						}
					}
				}while (opc != 1 && opc != 2);
				Texto_centrado("Gracias por usar el programa.", 1);
				break;
			}
			case 1:{
				system ("cls");
				Administracion.GestionarCursos(Colegio);
				system ("cls");
				break;
			}
			case 2:{
				system ("cls");
				Administracion.GestionarCursoEspe(Colegio);
				system ("Pause");
				system ("cls");
				break;
			}
			case 3:{
				system ("cls");
				Texto_Ascii("Colegio La2bleA");
				if (Colegio.CantidadEstudiantes() > 0)
					Colegio.ImprimirEstudiantes(0);
				else{
					cout << endl;
					Texto_centrado("La lista de estudiantes se encuentra vacía.", 1);
				}
				system ("Pause");
				system ("cls");
				break;
			}
			case 4:{
				Colegio.GuardarArchivos();
				Texto_centrado("Archivos guardados con exito.", 1);
				system ("Pause");
				system ("cls");
				break;
			}
			default:{
				Texto_centrado("Opción incorrecta, ingrese una opción valida", 1);
				system ("Pause");
				system ("cls");
				break;
			}
		}
	}while(op != 0);
}

void Texto_centrado(string Texto, int y){
	int x = Texto.size();
	x = (120 - x)/2;
	if (y > 0){
		for (int j = 0; j < x; j++){
					cout << " ";
				}
		cout << Texto << endl;
	}
	else {
		for (int j = 0; j < x; j++){
					cout << " ";
				}
		cout << Texto;
	}
	
}

void Texto_Ascii (string Texto){
	int x = Texto.size();
	x *= 4;
	x = (120 - x)/2;
	for (int i = 0; i < Texto.size(); i++){
		if (i == 0){
			for (int j = 0; j < x; j++){
				cout << " ";
			}
		}
		if (Texto[i] == '1')
			cout << " ## ";
		if (Texto[i] == '2')
			cout << "### ";
		if (Texto[i] == '3')
			cout << "### ";
		if (Texto[i] == '4')
			cout << "# # ";
		if (Texto[i] == '5')
			cout << "### ";
		if (Texto[i] == '6')
			cout << "### ";
		if (Texto[i] == '7')
			cout << "### ";
		if (Texto[i] == '8')
			cout << "### ";
		if (Texto[i] == '9')
			cout << "### ";
		if (Texto[i] == '0')
			cout << "### ";
		if (Texto[i] == 'A' || Texto[i] == 'a')
			cout << " #  ";
		if (Texto[i] == 'B' || Texto[i] == 'b')
			cout << "##  ";
		if (Texto[i] == 'C' || Texto[i] == 'c')
			cout << " ## ";
		if (Texto[i] == 'D' || Texto[i] == 'd')
			cout << "##  ";
		if (Texto[i] == 'E' || Texto[i] == 'e')
			cout << "### ";
		if (Texto[i] == 'F' || Texto[i] == 'f')
			cout << "### ";
		if (Texto[i] == 'G' || Texto[i] == 'g')
			cout << " ## ";
		if (Texto[i] == 'H' || Texto[i] == 'h')
			cout << "# # ";
		if (Texto[i] == 'I' || Texto[i] == 'i')
			cout << "### ";
		if (Texto[i] == 'J' || Texto[i] == 'j')
			cout << " ## ";
		if (Texto[i] == 'K' || Texto[i] == 'k')
			cout << "# # ";
		if (Texto[i] == 'L' || Texto[i] == 'l')
			cout << "#   ";
		if (Texto[i] == 'M' || Texto[i] == 'm')
			cout << "# # ";
		if (Texto[i] == 'N' || Texto[i] == 'n')
			cout << "### ";
		if (Texto[i] == 'Ñ' || Texto[i] == 'ñ')
			cout << "*** ";
		if (Texto[i] == 'O' || Texto[i] == 'o')
			cout << " #  ";
		if (Texto[i] == 'P' || Texto[i] == 'p')
			cout << "##  ";
		if (Texto[i] == 'Q' || Texto[i] == 'q')
			cout << " #  ";
		if (Texto[i] == 'R' || Texto[i] == 'r')
			cout << "##  ";
		if (Texto[i] == 'S' || Texto[i] == 's')
			cout << " ## ";
		if (Texto[i] == 'T' || Texto[i] == 't')
			cout << "### ";
		if (Texto[i] == 'U' || Texto[i] == 'u')
			cout << "# # ";
		if (Texto[i] == 'V' || Texto[i] == 'v')
			cout << "# # ";
		if (Texto[i] == 'W' || Texto[i] == 'w')
			cout << "# # ";
		if (Texto[i] == 'X' || Texto[i] == 'x')
			cout << "# # ";
		if (Texto[i] == 'Y' || Texto[i] == 'y')
			cout << "# # ";
		if (Texto[i] == 'Z' || Texto[i] == 'z')
			cout << "### ";
		if (Texto[i] == ' ')
			cout << "    ";
	} cout << endl;
	for (int i = 0; i < Texto.size(); i++){
		if (i == 0){
			for (int j = 0; j < x; j++){
				cout << " ";
			}
		}
		if (Texto[i] == '1')
			cout << "# # ";
		if (Texto[i] == '2')
			cout << "  # ";
		if (Texto[i] == '3')
			cout << "  # ";
		if (Texto[i] == '4')
			cout << "# # ";
		if (Texto[i] == '5')
			cout << "#   ";
		if (Texto[i] == '6')
			cout << "#   ";
		if (Texto[i] == '7')
			cout << "  # ";
		if (Texto[i] == '8')
			cout << "# # ";
		if (Texto[i] == '9')
			cout << "# # ";
		if (Texto[i] == '0')
			cout << "# # ";
		if (Texto[i] == 'A' || Texto[i] == 'a')
			cout << "# # ";
		if (Texto[i] == 'B' || Texto[i] == 'b')
			cout << "# # ";
		if (Texto[i] == 'C' || Texto[i] == 'c')
			cout << "#   ";
		if (Texto[i] == 'D' || Texto[i] == 'd')
			cout << "# # ";
		if (Texto[i] == 'E' || Texto[i] == 'e')
			cout << "#   ";
		if (Texto[i] == 'F' || Texto[i] == 'f')
			cout << "#   ";
		if (Texto[i] == 'G' || Texto[i] == 'g')
			cout << "#   ";
		if (Texto[i] == 'H' || Texto[i] == 'h')
			cout << "# # ";
		if (Texto[i] == 'I' || Texto[i] == 'i')
			cout << " #  ";
		if (Texto[i] == 'J' || Texto[i] == 'j')
			cout << "  # ";
		if (Texto[i] == 'K' || Texto[i] == 'k')
			cout << "# # ";
		if (Texto[i] == 'L' || Texto[i] == 'l')
			cout << "#   ";
		if (Texto[i] == 'M' || Texto[i] == 'm')
			cout << "### ";
		if (Texto[i] == 'N' || Texto[i] == 'n')
			cout << "# # ";
		if (Texto[i] == 'Ñ' || Texto[i] == 'ñ')
			cout << "### ";
		if (Texto[i] == 'O' || Texto[i] == 'o')
			cout << "# # ";
		if (Texto[i] == 'P' || Texto[i] == 'p')
			cout << "# # ";
		if (Texto[i] == 'Q' || Texto[i] == 'q')
			cout << "# # ";
		if (Texto[i] == 'R' || Texto[i] == 'r')
			cout << "# # ";
		if (Texto[i] == 'S' || Texto[i] == 's')
			cout << "#   ";
		if (Texto[i] == 'T' || Texto[i] == 't')
			cout << " #  ";
		if (Texto[i] == 'U' || Texto[i] == 'u')
			cout << "# # ";
		if (Texto[i] == 'V' || Texto[i] == 'v')
			cout << "# # ";
		if (Texto[i] == 'W' || Texto[i] == 'w')
			cout << "# # ";
		if (Texto[i] == 'X' || Texto[i] == 'x')
			cout << "# # ";
		if (Texto[i] == 'Y' || Texto[i] == 'y')
			cout << "# # ";
		if (Texto[i] == 'Z' || Texto[i] == 'z')
			cout << "  # ";
		if (Texto[i] == ' ')
			cout << "    ";
	} cout << endl;
	for (int i = 0; i < Texto.size(); i++){
		if (i == 0){
			for (int j = 0; j < x; j++){
				cout << " ";
			}
		}
		if (Texto[i] == '1')
			cout << "  # ";
		if (Texto[i] == '2')
			cout << "  # ";
		if (Texto[i] == '3')
			cout << " ## ";
		if (Texto[i] == '4')
			cout << "### ";
		if (Texto[i] == '5')
			cout << "### ";
		if (Texto[i] == '6')
			cout << "### ";
		if (Texto[i] == '7')
			cout << " ## ";
		if (Texto[i] == '8')
			cout << "### ";
		if (Texto[i] == '9')
			cout << "### ";
		if (Texto[i] == '0')
			cout << "# # ";
		if (Texto[i] == 'A' || Texto[i] == 'a')
			cout << "### ";
		if (Texto[i] == 'B' || Texto[i] == 'b')
			cout << "##  ";
		if (Texto[i] == 'C' || Texto[i] == 'c')
			cout << "#   ";
		if (Texto[i] == 'D' || Texto[i] == 'd')
			cout << "# # ";
		if (Texto[i] == 'E' || Texto[i] == 'e')
			cout << "##  ";
		if (Texto[i] == 'F' || Texto[i] == 'f')
			cout << "##  ";
		if (Texto[i] == 'G' || Texto[i] == 'g')
			cout << "# # ";
		if (Texto[i] == 'H' || Texto[i] == 'h')
			cout << "### ";
		if (Texto[i] == 'I' || Texto[i] == 'i')
			cout << " #  ";
		if (Texto[i] == 'J' || Texto[i] == 'j')
			cout << "  # ";
		if (Texto[i] == 'K' || Texto[i] == 'k')
			cout << "# # ";
		if (Texto[i] == 'L' || Texto[i] == 'l')
			cout << "#   ";
		if (Texto[i] == 'M' || Texto[i] == 'm')
			cout << "### ";
		if (Texto[i] == 'N' || Texto[i] == 'n')
			cout << "# # ";
		if (Texto[i] == 'Ñ' || Texto[i] == 'ñ')
			cout << "# # ";
		if (Texto[i] == 'O' || Texto[i] == 'o')
			cout << "# # ";
		if (Texto[i] == 'P' || Texto[i] == 'p')
			cout << "##  ";
		if (Texto[i] == 'Q' || Texto[i] == 'q')
			cout << "# # ";
		if (Texto[i] == 'R' || Texto[i] == 'r')
			cout << "##  ";
		if (Texto[i] == 'S' || Texto[i] == 's')
			cout << " #  ";
		if (Texto[i] == 'T' || Texto[i] == 't')
			cout << " #  ";
		if (Texto[i] == 'U' || Texto[i] == 'u')
			cout << "# # ";
		if (Texto[i] == 'V' || Texto[i] == 'v')
			cout << "# # ";
		if (Texto[i] == 'W' || Texto[i] == 'w')
			cout << "### ";
		if (Texto[i] == 'X' || Texto[i] == 'x')
			cout << " #  ";
		if (Texto[i] == 'Y' || Texto[i] == 'y')
			cout << " #  ";
		if (Texto[i] == 'Z' || Texto[i] == 'z')
			cout << " #  ";
		if (Texto[i] == ' ')
			cout << "    ";
	} cout << endl;
	for (int i = 0; i < Texto.size(); i++){
		if (i == 0){
			for (int j = 0; j < x; j++){
				cout << " ";
			}
		}
		if (Texto[i] == '1')
			cout << "  # ";
		if (Texto[i] == '2')
			cout << " #  ";
		if (Texto[i] == '3')
			cout << "  # ";
		if (Texto[i] == '4')
			cout << "  # ";
		if (Texto[i] == '5')
			cout << "  # ";
		if (Texto[i] == '6')
			cout << "# # ";
		if (Texto[i] == '7')
			cout << "  # ";
		if (Texto[i] == '8')
			cout << "# # ";
		if (Texto[i] == '9')
			cout << "  # ";
		if (Texto[i] == '0')
			cout << "# # ";
		if (Texto[i] == 'A' || Texto[i] == 'a')
			cout << "# # ";
		if (Texto[i] == 'B' || Texto[i] == 'b')
			cout << "# # ";
		if (Texto[i] == 'C' || Texto[i] == 'c')
			cout << "#   ";
		if (Texto[i] == 'D' || Texto[i] == 'd')
			cout << "# # ";
		if (Texto[i] == 'E' || Texto[i] == 'e')
			cout << "#   ";
		if (Texto[i] == 'F' || Texto[i] == 'f')
			cout << "#   ";
		if (Texto[i] == 'G' || Texto[i] == 'g')
			cout << "# # ";
		if (Texto[i] == 'H' || Texto[i] == 'h')
			cout << "# # ";
		if (Texto[i] == 'I' || Texto[i] == 'i')
			cout << " #  ";
		if (Texto[i] == 'J' || Texto[i] == 'j')
			cout << "# # ";
		if (Texto[i] == 'K' || Texto[i] == 'k')
			cout << "# # ";
		if (Texto[i] == 'L' || Texto[i] == 'l')
			cout << "#   ";
		if (Texto[i] == 'M' || Texto[i] == 'm')
			cout << "# # ";
		if (Texto[i] == 'N' || Texto[i] == 'n')
			cout << "# # ";
		if (Texto[i] == 'Ñ' || Texto[i] == 'ñ')
			cout << "# # ";
		if (Texto[i] == 'O' || Texto[i] == 'o')
			cout << "# # ";
		if (Texto[i] == 'P' || Texto[i] == 'p')
			cout << "#   ";
		if (Texto[i] == 'Q' || Texto[i] == 'q')
			cout << " ## ";
		if (Texto[i] == 'R' || Texto[i] == 'r')
			cout << "# # ";
		if (Texto[i] == 'S' || Texto[i] == 's')
			cout << "  # ";
		if (Texto[i] == 'T' || Texto[i] == 't')
			cout << " #  ";
		if (Texto[i] == 'U' || Texto[i] == 'u')
			cout << "# # ";
		if (Texto[i] == 'V' || Texto[i] == 'v')
			cout << "# # ";
		if (Texto[i] == 'W' || Texto[i] == 'w')
			cout << "### ";
		if (Texto[i] == 'X' || Texto[i] == 'x')
			cout << "# # ";
		if (Texto[i] == 'Y' || Texto[i] == 'y')
			cout << " #  ";
		if (Texto[i] == 'Z' || Texto[i] == 'z')
			cout << "#   ";
		if (Texto[i] == ' ')
			cout << "    ";
	} cout << endl;
		for (int i = 0; i < Texto.size(); i++){
			if (i == 0){
			for (int j = 0; j < x; j++){
				cout << " ";
			}
		}
		if (Texto[i] == '1')
			cout << "  # ";
		if (Texto[i] == '2')
			cout << "### ";
		if (Texto[i] == '3')
			cout << "### ";
		if (Texto[i] == '4')
			cout << "  # ";
		if (Texto[i] == '5')
			cout << "### ";
		if (Texto[i] == '6')
			cout << "### ";
		if (Texto[i] == '7')
			cout << "  # ";
		if (Texto[i] == '8')
			cout << "### ";
		if (Texto[i] == '9')
			cout << "### ";
		if (Texto[i] == '0')
			cout << "### ";
		if (Texto[i] == 'A' || Texto[i] == 'a')
			cout << "# # ";
		if (Texto[i] == 'B' || Texto[i] == 'b')
			cout << "##  ";
		if (Texto[i] == 'C' || Texto[i] == 'c')
			cout << " ## ";
		if (Texto[i] == 'D' || Texto[i] == 'd')
			cout << "##  ";
		if (Texto[i] == 'E' || Texto[i] == 'e')
			cout << "### ";
		if (Texto[i] == 'F' || Texto[i] == 'f')
			cout << "#   ";
		if (Texto[i] == 'G' || Texto[i] == 'g')
			cout << " ## ";
		if (Texto[i] == 'H' || Texto[i] == 'h')
			cout << "# # ";
		if (Texto[i] == 'I' || Texto[i] == 'i')
			cout << "### ";
		if (Texto[i] == 'J' || Texto[i] == 'j')
			cout << " #  ";
		if (Texto[i] == 'K' || Texto[i] == 'k')
			cout << "# # ";
		if (Texto[i] == 'L' || Texto[i] == 'l')
			cout << "### ";
		if (Texto[i] == 'M' || Texto[i] == 'm')
			cout << "# # ";
		if (Texto[i] == 'N' || Texto[i] == 'n')
			cout << "# # ";
		if (Texto[i] == 'Ñ' || Texto[i] == 'ñ')
			cout << "# # ";
		if (Texto[i] == 'O' || Texto[i] == 'o')
			cout << " #  ";
		if (Texto[i] == 'P' || Texto[i] == 'p')
			cout << "#   ";
		if (Texto[i] == 'Q' || Texto[i] == 'q')
			cout << "  # ";
		if (Texto[i] == 'R' || Texto[i] == 'r')
			cout << "# # ";
		if (Texto[i] == 'S' || Texto[i] == 's')
			cout << "##  ";
		if (Texto[i] == 'T' || Texto[i] == 't')
			cout << " #  ";
		if (Texto[i] == 'U' || Texto[i] == 'u')
			cout << "### ";
		if (Texto[i] == 'V' || Texto[i] == 'v')
			cout << " #  ";
		if (Texto[i] == 'W' || Texto[i] == 'w')
			cout << "# # ";
		if (Texto[i] == 'X' || Texto[i] == 'x')
			cout << "# # ";
		if (Texto[i] == 'Y' || Texto[i] == 'y')
			cout << " #  ";
		if (Texto[i] == 'Z' || Texto[i] == 'z')
			cout << "### ";
		if (Texto[i] == ' ')
			cout << "    ";
	} cout << endl;
}



