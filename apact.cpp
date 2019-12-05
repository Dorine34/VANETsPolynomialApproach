#include <cstdlib>  
#include <fstream>
#include <vector>
#include <iostream>
#include <string>
#include <stdio.h> 
#include <stdlib.h> 


using namespace std; 
float EPSILON =0.5;

/*
ALGO : callThroughputWifi
INPUT : executable file with two communication technologies (wifi-?)
OUTPUT : a file "throughput" with reunited throughputs  
*/
void 
callThroughputWifi()
{
    system( "./waf --run \"scratch/wifi-wifi --transport=Udp --udpPacketSize=1500 --udpRate=85Mbps\""); 
	system( "./waf --run \"scratch/wifi-laa --transport=Udp --udpPacketSize=1500 --udpRate=85Mbps\"");   
    system( "./waf --run \"scratch/wifi-lte --transport=Udp --udpPacketSize=1500 --udpRate=85Mbps\"");  
}

/*
ALGO : callThroughput
INPUT : executable file with two communication technologies  (lte-?)
OUTPUT : a file "throughput" with reunited throughputs  
*/
void 
callThroughputLTE()
{
    system( "./waf --run \"scratch/lte-wifi --transport=Udp --udpPacketSize=1500 --udpRate=85Mbps\"");  
	system( "./waf --run \"scratch/lte-laa --transport=Udp --udpPacketSize=1500 --udpRate=85Mbps\"");  
    system( "./waf --run \"scratch/lte-lte --transport=Udp --udpPacketSize=1500 --udpRate=85Mbps\"");  
}

/*
ALGO : callThroughput
INPUT : executable file with two communication technologies (laa-?)
OUTPUT : a file "throughput" with reunited throughputs  
*/
void 
callThroughputLAA()
{
    system( "./waf --run \"scratch/laa-wifi --transport=Udp --udpPacketSize=1500 --udpRate=85Mbps\"");  
	system( "./waf --run \"scratch/laa-laa --transport=Udp --udpPacketSize=1500 --udpRate=85Mbps\"");  
    system( "./waf --run \"scratch/laa-lte --transport=Udp --udpPacketSize=1500 --udpRate=85Mbps\"");  
}

/*
ALGO : getVector
INPUT : 
OUTPUT : a vector with throughputs  
*/
vector <double> 
getVector ()
{
	ifstream fichier("throughput");
	int npos=0;
	vector<double> v1;
	size_t found,dep;
	if(fichier)
	{
		string ligne;
		while(getline(fichier, ligne)) 
		{
			found = ligne.find_first_of(' ');
			dep=0;
 			while (found!=std::string::npos)
			{
				double throughput1=atof(ligne.substr (dep,found-dep).c_str());
				v1.push_back(throughput1);
				dep=found+1;
				found=ligne.find_first_of(' ',found+1);
	  		}
		}	
	}
	else
	{
		cout << "ERROR : Impossible to open the throughput file." << endl;
	}
	return v1;
}


/*
ALGO : election
INPUT : vector of throughput
OUTPUT : Index of the communication technology with the best average throughput  
*/
int 
election(vector<double> v1)
{
	double maxT=0;
	int maxInd=0;
	for (int i = 0; i < v1.size(); i++) 
	{
		if (i%2==0)
		{
			if ((v1[i]+v1[i+1])/2>maxT)
			{
				maxT=(v1[i]+v1[i+1])/2;
				maxInd=i/2;
			}
		}
	}
	return maxInd;
}



/*
ALGO : resultat
INPUT : vector of throughput
OUTPUT : out of the best communication technology  
*/
void 
resultat(int elect)
{
	switch (elect)
    {
    cout<<"********************"<<endl;
    case 0:
        cout<<"WIFI elected"<<endl;
        break;
    case 1:
    	cout<<"LAA elected"<<endl;
        break;
    case 2:
    	cout<<"LTE elected"<<endl;
        break;
    default:
    	cout<<"ERROR"<<endl;
        break;
    }
}

/*
ALGO : clearThroughput
INPUT : file throughput
OUTPUT : empty file throughput
*/
void 
clearThroughput()
{
	FILE* fichier = NULL; 
	fichier = fopen("throughput", "w+"); 
	fclose (fichier);
}



/*
ALGO : exactSol
INPUT : vector of corresponding throughput
OUTPUT : empty file throughput
*/
void 
exactSol(vector<double>  vWIFI, int nbTC)
{
	int nbelmts=3;
	FILE* fichier = NULL; 
	fichier = fopen("simplex/data.dat", "w+"); 
	if (fichier != NULL) 
	{
		fprintf(fichier,"data;\n\nparam M := %d;\n\nparam n := 3;\n\nparam t := 1 1", nbTC);
		for (int i=1; i<nbelmts;i++)
		{
			fprintf(fichier,"\n\t\t\t %d 1",i+1 );
		}
		fprintf(fichier,";\nparam v := 1 %f",vWIFI.at(0));
		for (int i=1; i<nbelmts;i++)
		{
			fprintf(fichier,"\n\t\t\t %d %f",i+1, vWIFI.at(i) );
		}
		fprintf(fichier,";\nend;\n");
	} 
	else 
	{ 
		printf("Impossible d'ouvrir le fichier"); 
	}
	fclose (fichier);
	system( "glpsol --model simplex/sac_a_dos.mod --data simplex/data.dat");  
}


/*
ALGO : max
INPUT : 2 numbers
OUTPUT : the maximum number
*/
int 
max(int a, int b) {
	return (a > b)? a : b; 
} 
  
/*
ALGO : knapSack
INPUT : W size of Sack, wt cost, val value of items, n number of items 
OUTPUT : the best possible items in a sack, LocalSearchAlgorithm
*/
int
knapSack(int W, int wt[], float val[], int n) 
{ 
	int i, w, k; 
	k=0;
	float K[n+1][W+1]; 
  
	for (i = 0; i <= n; i++) 
	{ 
		for (w = 0; w <= W; w++) 
		{ 
			if (i==0 || w==0)
			{
				K[i][w] = 0;
			} 
			else
			{
				if (wt[i-1] <= w) 
				{
					K[i][w] = max(val[i-1] + K[i-1][w-wt[i-1]],  K[i-1][w]); 	
					k=i-1;
				}
				else
				{    
					K[i][w] = K[i-1][w];
				} 
			}
		} 
	} 
	return k; 
} 


/*
ALGO : electionBeta
INPUT : vector associated with throughput
OUTPUT : table of values associated 
			with the beta approximation of the knapsack
*/
void
electionBeta(vector<double> v1, float* valS )
{
	float k=3/EPSILON;
	float max=0;
	for (int i=0; i<3;i++)
	{
		if(v1.at(i)>max)
		{
			max=v1.at(i);
		}
	}
	for (int i=0; i<3;i++)
	{
		valS[i]=v1.at(i)*k/max;
	}
}

/*
ALGO : electionKnapSack
INPUT : values available
OUTPUT : the index of communication technology chosen
*/
int 
electionKnapSack(vector<double> v1)
{
	int wt[3];
	float val[3];
	for (int i = 0; i < v1.size(); i++) 
	{
		if (i%2==0)
		{
			wt[i/2]=1;
			val[i/2]=v1[i+1];
		}
	}
	float valS [3] ;
	electionBeta(v1, valS);

	return knapSack(1,wt,valS,3);
}

/*
ALGO : vModifiedA
INPUT : different vector of throughput according communication technology chosen and the corresponding choice
OUTPUT : the vector modified corresponding to the choice
*/
vector <double> 
vModifiedA (
			int Achoice,  
			vector<double>  vWIFI,
			vector<double>  vLAA, 
			vector<double> vLTE)
{
	vector<double> vModified =getVector ();
		switch (Achoice)
		{
			cout<<"********************"<<endl;
		case 0:
			cout<<"WIFI elected"<<endl;
			return vWIFI;
			break;
		case 1:
			cout<<"LAA elected"<<endl;
			return vLAA;
			break;
		case 2:
			cout<<"LTE elected"<<endl;
			return vLTE;
			break;
		default:
			cout<<"ERROR"<<endl;
			break;
	}
	return vModified;
}

/*
ALGO : initialiserMatrix
INPUT : one matrix and vectors of several communication technologies
OUTPUT : matrix modified according to different communication technologies
*/
void 
initialiserMatrix(
		double (&matrix)[3][6], 
		size_t NbLines, 
		vector<double>  vWIFI,
		vector<double>  vLAA, 
		vector<double> vLTE) 
{ 
	size_t i,j; 
	for(i = 0; i < NbLines; i++)
	{
		switch (i)
		{
			cout<<"********************"<<endl;
			case 0:
			cout<<"WIFI elected"<<endl;
			for (j = 0; j < vWIFI.size(); j++) 
			{
				matrix[i][j] = vWIFI.at(j);
			}
			break;
		case 1:
			cout<<"LAA elected"<<endl;
			for (j = 0; j < vLAA.size(); j++) 
			{
				matrix[i][j] = vLAA.at(j);
			}
			break;
		case 2:
			cout<<"LTE elected"<<endl;
			for (j = 0; j < vLTE.size(); j++) 
			{
				matrix[i][j] = vLTE.at(j);
			}        	
			break;
		default:
			cout<<"ERROR"<<endl;
			break;
		}
	}  
} 
/*
ALGO : main
INPUT : two nodes with LTE, Wi-FI and LAA
OUTPUT : These two operator are elected
RK :
*/
int 
main()  
{  
	int Achoice =0; 
	int Bchoice =0;

	//vectors creation


	callThroughputWifi();
	vector<double> vWIFI =getVector ();
	resultat(election(vWIFI));
	clearThroughput();

	callThroughputLAA();
	vector<double> vLAA =getVector ();
	resultat(election(vLAA));
	clearThroughput();

	callThroughputLTE();
	vector<double> vLTE =getVector ();
	resultat(election(vLTE));
	clearThroughput();

	//matrix creation
	/*
	double matrix[3][6];//3 lines, 6columns
	initialiserMatrix(matrix, 3, vWIFI, vLAA, vLTE);
	*/
	//SearchAlgorithm
	cout<<endl;

	for (int i=0; i<3;i++)
	{
		Achoice=electionKnapSack(vModifiedA(Achoice, vWIFI, vLAA, vLTE ));
		Bchoice=electionKnapSack(vModifiedA(Bchoice, vWIFI, vLAA, vLTE ));
	}	
	//Resultats
	cout<<"Operator A : "; resultat(Achoice); cout<<endl;
	cout<<"Operator B : "; resultat(Bchoice); cout<<endl;
	exactSol(vWIFI,1);
	return 0;
}
