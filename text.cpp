#include<bits/stdc++.h>
using namespace std;
int main()
{
    string line,deleteMovie;
            cout<<"Movie to delete: movieTitle(movieYear): ";
            cin>>deleteMovie;
            ifstream file;
            ofstream outfile;
            file.open("final.txt");
            outfile.open("newM.txt");
            while(getline(file,line))
            {
                if(line!=deleteMovie)
                    outfile<<line<<endl;
            }
            outfile.close();
            file.close();
            remove("final.txt");
            rename("newM.txt","final.txt");

}
