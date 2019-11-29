#include <cstdlib>  
#include <fstream>
#include <vector>
#include <iostream>
#include <string>


using namespace std; 


/*
ALGO : callThroughput
INPUT : executable file with two communication technologies
OUTPUT : a file "throughput" with reunited throughputs  
*/
void 
callThroughput()
{
	system( "./waf --run \"scratch/wifi-laa --transport=Udp --udpPacketSize=1500 --udpRate=85Mbps\"");  
    system( "./waf --run \"scratch/wifi-wifi --transport=Udp --udpPacketSize=1500 --udpRate=85Mbps\"");  
    system( "./waf --run \"scratch/wifi-lte --transport=Udp --udpPacketSize=1500 --udpRate=85Mbps\"");  
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
void resultat(int elect)
{
	switch (elect)
    {

    case 0:
        cout<<"LAA elected"<<endl;
        break;
    case 1:
    	cout<<"WIFI elected"<<endl;
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
ALGO : main
INPUT : 
OUTPUT : best communication technology  
REMARK : "main" procedure works in 2 steps:
	1-exploration, with the collect of throughput
	2-exploitation, with the best technology elected
*/
int 
main()  
{  
	callThroughput();
	vector<double> v1 =getVector ();
	resultat(election(v1));
	return 0;
}