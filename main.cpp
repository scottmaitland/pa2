#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>

using namespace std;

int main(int argc, char* argv[])
{
    string line;
    string buf;
    string path = argv[1];
    string outputPath = argv[2];
    string output2Path = argv[3];
    //cout << path << endl;
    ifstream myfile(path.c_str());
    int line_count = 0;
    vector<string> tokens;

    //cout << "Getting file from: " << path << endl;
    //cout << "Outputing file to: " << outputPath << endl;
    if (myfile.is_open())
    {
        while(getline (myfile,line))
        {
            stringstream ss(line);
            while (ss >> buf)
            {
                tokens.push_back(buf);
            }
        }
    }
    else
    {
        cout << "Could not open file" << endl;
    }
    myfile.close();

    ofstream output (outputPath.c_str());

    string line2;
    string buf2;
    vector<int> testTrainArray;
    vector<string> classArray;
    for(int i = 0; i < tokens.size(); i++)
    {
        //cout << "Opening document " << i << " documents name: " << tokens[i] << endl;
        ifstream document(tokens[i].c_str());
        if(tokens[i].find("test") == std::string::npos)
        {
            unsigned f = tokens[i].find("/");
            string x = tokens[i].substr(f+1, std::string::npos);
            unsigned l = x.find("/");
            string s = tokens[i].substr(f+1,l);
            testTrainArray.push_back(0);
            classArray.push_back(s);
        }
        else
        {
            unsigned f = tokens[i].find("/");
            string x = tokens[i].substr(f+1, std::string::npos);
            unsigned l = x.find("/");
            string s = tokens[i].substr(f+1,l);
            testTrainArray.push_back(1);
            classArray.push_back(s);
        }
        if( document.is_open())
        {
            while(getline(document, line2))
            {
                stringstream ss(line2);
                while(ss >> buf2)
                {
                    output << buf2 << " ";
                }
            }
        }
        else
        {
            cout << "Could not open " << tokens[i] << endl;
        }
        output << endl;
        document.close();
    }

    ofstream output2 (output2Path.c_str());
    for(int i = 0; i < testTrainArray.size(); i++)
    {
        output2 << testTrainArray[i] << " " << classArray[i] << endl;
    }
    return 0;
}

