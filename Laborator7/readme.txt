/=== Utilizare ===/

Mouse SUS-JOS 
Avionul poate fi deplasat in sus si in jos utilizand mouse-ul.

Tasta M
Camera poate fi trecuta dintr-o stare in alta (fps <-> clasic) prin apasarea tastei M.

Tasta R
Reluarea jocului dupa ce s-a terminat se face cu tasta R.

Tasta Z
Deplaseaza camera in partea stanga cu 1 unitate.

Tasta X
Deplaseaza camera in partea dreapta cu 1 unitate.


/=== Implementare ===/

Functia bool intersect(Sfera sphere, Cutie box) returneaza true, daca sfera si cubul specificat se intersecteaza.

Avionul contine un un dreptunghi deformat in blender pentru a arata mai realist.

Obstacolele sunt sfere de culoare verde care apar aleator.

Marea este reprezentata de un cilindru deformat in Blender care se roteste in continuu.

Variabilele de clasa creeate sunt
	// varibile utilizate pentru iluminare
	glm::vec3 lightPosition;
	unsigned int materialShininess;
	float materialKd;
	float materialKs;
		
	// locul pe axa Oy unde se afla avionul
	float deplasare;
		
	// locul pe axa Oy unde se afla avionul inainte
	int oldMouseY;
		
	// rotatia elicei
	int rotatieElice;
	// rotatia cilindrului cu marea
	int rotatieMare;
		
	// daca este setata camera fps
	bool fpsCamera;
		
	// axa pe care zboara avionului
	int pozitieZ;
	
	//y pentru fiecare obstacol generat/ maxim 1000 de obstacole
	double YObstacole[1000];
	
	// numarul obstacolului curent
	int nrObstacol=1000;
	
	// deplasasarea pe axa Ox
	double axaX;
	
	// diferenta intre 2 afisari de obstacole pe axa Ox
	// generata random
	double offset;
	
	// obiectul avion folosit pentru detectia coliziunilor	
	Cutie avion;
	
	// primul obstacol desenat 
	Sfera obstacol1;
	
	// al 2-lea obstacol desenat
	Sfera obstacol2;
	
	// daca avionul se prabuseste
	bool prabusireAvion;
	
	// daca primul obstacol desenat a fost lovit
	bool obstacol1Lovit;
	
	// daca cel de-al 2-lea obstacol desenat a fost lovit
	bool obstacol2Lovit;
	
	// daca se afiseaza primul obstacol
	bool obstacol1Afisat;
	
	// daca se afiseaza al 2-lea obstacol
	bool obstacol2Afisat;
	
	// numarul de deplasari in spate ale avionului
	// dupa ce s-a lovits
	int nrAfisariLovitura;
	
	// nr vieti ale pilotului
	int nrVieti = 3;