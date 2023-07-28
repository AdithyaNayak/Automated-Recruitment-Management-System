#include <iostream>
#include <fstream>
#include <vector>
#include<string>
#include<filesystem>
#include<typeinfo>

using namespace std;
namespace fs = std::filesystem;

class InputResumes;

namespace resumeDetails
{
    class Resume 
    {

        private:
        void lower_string(string str)
        {

            for(int i=0;str[i]!='\0';i++)
            {
                if (str[i] >= 'A' && str[i] <= 'Z')    
                    str[i] = str[i] + 32;         
            }
            //cout<<"\n The string in lower case: "<< str;
        }


        public:
        string name;
        string education;
        string skills;
        string domain;
        string exp;

        friend InputResumes;

        Resume()
        {

        }
    };

}


class InputResumes
{
    public:

    string convert(string s1)
    {
        resumeDetails::Resume r1;
        r1.lower_string(s1);

        return s1;
    }

    vector<resumeDetails::Resume> readResumes(const vector<string>& filenames) 
    {
        vector<resumeDetails::Resume> resumes;

        for (const auto& filename : filenames) 
        {
            string space = "\t";
            ifstream file(filename);

            if (!file) 
            {
                cerr << "Error opening file: " << filename << endl;
                continue;
            }

            resumeDetails::Resume resume;
            getline(file, resume.name);
            resume.name.erase(0, 6);
            resume.name.append(space);
            convert(resume.name);
            getline(file, resume.education);
            resume.education.erase(0, 11);
            resume.education.append(space);
            convert(resume.education);
            getline(file, resume.skills);
            resume.skills.erase(0, 8);
            resume.skills.append(space);
            convert(resume.skills);
            getline(file, resume.domain);
            resume.domain.erase(0, 8);
            resume.domain.append(space);
            convert(resume.domain);
            getline(file, resume.exp);
            resume.exp.erase(0, 12);
            resume.exp.append(space);
            convert(resume.exp);
        
            resumes.push_back(resume);
            file.close();
        }

        return resumes;
    }

};

class Filter: public InputResumes
{
    private:

    bool isResumeDuplicate(const resumeDetails::Resume& newResume, const vector<resumeDetails::Resume>& resumes)
    {
        for (const auto& resume : resumes)
        {
            if (newResume.name == resume.name &&
                newResume.education == resume.education &&
                newResume.skills == resume.skills &&
                newResume.domain == resume.domain &&
                newResume.exp == resume.exp)
            {
                return true;
            }
        }
        return false;
    }

    public:

    //resumeDetails::Resume resume;

    vector<resumeDetails::Resume> filterResumes(const vector<resumeDetails::Resume>& resumes, const string& filter, const string& category) 
    {

        vector<resumeDetails::Resume> filteredResumes;

        if(category == "Name")
        {
            for (const auto& resume : resumes) 
            {
                if(resume.name.find(filter) != string::npos)
                {
                    
                    if (!isResumeDuplicate(resume, filteredResumes))
                    {
                        filteredResumes.push_back(resume);
                    }

                    //filteredResumes.push_back(resume);
                }
            }
        }

        else if(category == "Education")
        {
            for (const auto& resume : resumes) 
            {
                if(resume.education.find(filter) != string::npos)
                {                    
                    if (!isResumeDuplicate(resume, filteredResumes))
                    {
                        filteredResumes.push_back(resume);
                    }

                }
            }
        }

        else if(category == "Skills")
        {
            for (const auto& resume : resumes) 
            {
                if(resume.skills.find(filter) != string::npos)
                {
                    
                    if (!isResumeDuplicate(resume, filteredResumes))
                    {
                        filteredResumes.push_back(resume);
                    }

                }
            }
        }

        else if(category == "Domain")
        {
            for (const auto& resume : resumes) 
            {
                if(resume.domain.find(filter) != string::npos)
                {
                    
                    if (!isResumeDuplicate(resume, filteredResumes))
                    {
                        filteredResumes.push_back(resume);
                    }

                }
            }
        }

        else if(category == "Experience")
        {
            for (const auto& resume : resumes) 
            {
                if(resume.exp.find(filter) != string::npos)
                {
                    //if(resume )
                    
                    if (!isResumeDuplicate(resume, filteredResumes))
                    {
                        filteredResumes.push_back(resume);
                    }

                }
            }
        }

        else
        {
            cout << "Invalid category\n" << endl;
        }
/*      
        for (const auto& resume : resumes) 
        {
            if(resume.name.find(filter) != string::npos ||
                resume.education.find(filter) != string::npos ||
                resume.skills.find(filter) != string::npos || resume.domain.find(filter) != string::npos
                || resume.exp.find(filter) != string::npos)
            {
                filteredResumes.push_back(resume);
            }
        }

*/

        return filteredResumes;
    }

};


int main() 
{
    //InputResumes I1;
    Filter F1;
    //InputResumes I1;
    vector<string> filenames;// = { "resume1.txt", "resume2.txt", "resume3.txt"};

    
    
    char* folderPath = getenv("RESUME_FOLDER");

    if (folderPath == nullptr)
    {
        cout << "Environment variable RESUME_FOLDER_PATH not set. Please set it and try again." << endl;
        return 1;
    }

    string folderPathStr = folderPath;
    if (folderPathStr.back() != '/' && folderPathStr.back() != '\\')
    {
        folderPathStr += "/";
    }

    //vector<string> filenames;

    
    //std::vector<std::string> filenames;

    try
    {
        // Iterate over all files in the directory
        for (const auto& entry : fs::directory_iterator(folderPath))
        {
            // Check if the current entry is a regular file (not a directory)
            if (entry.is_regular_file())
            {
                // Get the file path and add it to the filenames vector
                filenames.push_back(entry.path().string());
            }
        }
    }

    catch (const exception& ex)
    {
        cerr << "Error listing files: " << ex.what() << endl;
        return 1;
    }

    // Now you have the filenames vector containing the paths to all the files in the folder
    for (const auto& filename : filenames)
    {
        cout << filename << endl;
    }

    cout << "\n" << endl;

    vector<resumeDetails::Resume> resumes = F1.readResumes(filenames);

    string filter, category, space = "\t", cont = "y";

    //cout << filter;
    //transform(filter.begin(), filter.end(), filter.begin(), ::toupper);
    static vector<resumeDetails::Resume> filteredResumes;

/*
    cout << "Enter category: ";
    getline(cin, category);


    cout << "Enter filter criteria: ";
    getline(cin, filter);

    filter.append(space);
    F1.convert(filter);
    //filteredResumes = F1.filterResumes(resumes, filter, category);

*/



    do
    {
        cout << "Enter category: " << endl;
        getline(cin, category);


        cout << "Enter filter criteria: " << endl;
        getline(cin, filter);

        filter.append(space);
        F1.convert(filter);
        filteredResumes = F1.filterResumes(resumes, filter, category);

        cout << "Continue?(y/n): " << endl;
        getline(cin, cont);
        
        cout << "\t" << endl;

    }while(cont == "y");

    if(filteredResumes.empty())
    {
        cout << "Not found" << endl;
    }

    else
    {
        for(const auto& resume : filteredResumes) 
        {
        cout << "Name: " << resume.name << endl;
        cout << "Education: " << resume.education << endl;
        cout << "Skills: " << resume.skills << endl;
        cout << "Domain: " << resume.domain << endl;
        cout << "Experience: " << resume.exp << endl;

        cout << "------------------------------------" << endl;
        }

    }

    const type_info& typeInfo = typeid(filteredResumes);

    cout << typeInfo.name() << endl;

    return 0;
}