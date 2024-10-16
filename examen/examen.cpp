#include <iostream>
#include <fstream>
#include <string>

#include <Windows.h> 
using namespace std;

struct type1 {
    string type;
    string categore;
};
struct Source {
     
    type1 type;
    string title;  
    string author;  
    string year; 
   

};


string toLoweCase(const string& line) {
    string str = line;
    for (size_t i = 0; i < str.length(); ++i) {
 
        if (str[i] >= '�' && str[i] <= '�') {
            str[i] = str[i] + 32;
        }
        else {
            str[i] = tolower(str[i]);
        }
    }
    return str;
}
void saveSourceToFile(const string& filename, const Source& source) {
    ofstream file(filename, ios::app);
    if (!file.is_open()) {
        cout << "������� �������� ����� ��� ������!" << endl;
        return;
    }
    if (toLoweCase(source.type.type) != "�����") {
        source.type.categore == "";
    }
    file << source.type.type << "," << source.title << "," << source.author << "," << source.year << "," << source.type.categore << endl;
      
    file.close();
}


void addSource1(Source*& sources, size_t& count, size_t& capacity, const string& filename) {
    if (count >= capacity) {
     
        capacity++;
        Source* newSources = new Source[capacity];
        for (size_t i = 0; i < count; ++i) {
            newSources[i] = sources[i];
        }
        delete[] sources;
        sources = newSources;
    }


    cout << "������ ��� ������� (�����, ������, ������): ";
    cin >> sources[count].type.type;
    cin.ignore(); 
    cout << "������ �����: ";
    getline(cin, sources[count].title);
    cout << "������ ������/�������: ";
    getline(cin, sources[count].author);
    cout << "������ �� �������: ";
    getline(cin, sources[count].year);
    if (toLoweCase(sources[count].type.type) == "�����") {
        cout << "������ �������� ������: ";
        getline(cin, sources[count].type.categore);
    }

 
    saveSourceToFile(filename, sources[count]);
    ++count;
    
}

void addSource2(Source*& sources, size_t& count, size_t& capacity, const string& filename,int n) {
    if (count >= capacity) {

        capacity+n;
        Source* newSources = new Source[capacity];
        for (size_t i = 0; i < count; ++i) {
            newSources[i] = sources[i];
        }
        delete[] sources;
        sources = newSources;
    }

    for (size_t i = 0; i < n; i++)
    {
        cout << "������ ��� ������� (�����, ������, ������): ";
        cin >> sources[count].type.type;
        cin.ignore();
        cout << "������ �����: ";
        getline(cin, sources[count].title);
        cout << "������ ������/�������: ";
        getline(cin, sources[count].author);
        cout << "������ �� �������: ";
        getline(cin, sources[count].year);
        if (toLoweCase(sources[count].type.type) == "�����") {
            cout << "������ �������� ������: ";
            getline(cin, sources[count].type.categore);
        }

        saveSourceToFile(filename, sources[count]);
        ++count;
    }
    

}
 


void viewSources(Source* sources, size_t count) {
    if (count == 0) {
        cout << "���� ����� �������." << endl;
        return;
    }

    cout << "������� � ��� �����:" << endl;
    cout << "========================" << endl;
    for (size_t i = 0; i < count; ++i) {
        cout << "������: " << i << endl;
        cout << "���: " << sources[i].type.type << endl;
        cout << "�����: " << sources[i].title << endl;
        cout << "�����/��������: " << sources[i].author << endl;
        cout << "г� �������: " << sources[i].year << endl;
        if (sources[i].type.type == "�����" or sources[i].type.type == "�����")
            cout << "�������� ������: " << sources[i].type.categore << endl;
    
        cout << "------------------------" << endl;
    }
}


void loadSourcesFromFile(const string& filename, Source*& sources, size_t& count, size_t& capacity) {
    ifstream file(filename);
    if (!file.is_open()) {
        cout << "������� �������� ����� ��� �������!" << endl;
        return;
    }

    string line;
    while (getline(file, line)) {
        if (count >= capacity) {
            
            capacity += count;
            Source* newSources = new Source[capacity];
            for (size_t i = 0; i < count; ++i) {
                newSources[i] = sources[i];
            }
            delete[] sources;
            sources = newSources;
        }

       
        size_t fieldIndex = 0;
        string field;
        size_t i = 0;

        while (i < line.length()) {
            if (line[i] == ',') {
              
                if (fieldIndex == 0) {
                    sources[count].type.type = field;
                }
                else if (fieldIndex == 1) {
                    sources[count].title = field;
                }
                else if (fieldIndex == 2) {
                    sources[count].author = field;
                }
                else if (fieldIndex == 3) {
                    sources[count].year = field;
                }
                else if (fieldIndex == 4) {
                    sources[count].type.categore = field;
                }
                field.clear(); 
                fieldIndex++;
            }
            else {
                field += line[i];
            }
            i++; 
        }

        if (fieldIndex == 3) {
            sources[count].year = field;
        }
        if (fieldIndex == 4) {
            sources[count].type.categore = field;
        }

        ++count; 
    }

    file.close();
   
}



void remove(Source*& sources, size_t& count, const size_t& index, const string& filename) {
    if (index >= count) {
        cout << "Error! Out of range." << endl;
        return;
    }

  
    Source* newSources = new Source[count - 1];


    for (size_t i = 0; i < count; i++) {
        if (i < index) {
            newSources[i] = sources[i]; 
        }
        else if (i > index) {
            newSources[i - 1] = sources[i]; 
        }
    }

    delete[] sources; 
    sources = newSources; 
    --count; 

   
    ofstream file(filename);
    if (!file.is_open()) {
        cout << "������� �������� ����� ��� ������!" << endl;
        return;
    }

    for (size_t i = 0; i < count; ++i) {
        if (toLoweCase(sources[i].type.type) != "�����") {
            sources[i].type.categore == "";
        }
        file << sources[i].type.type << "," << sources[i].title << "," << sources[i].author << "," << sources[i].year << "," << sources[i].type.categore << endl;
    }

    file.close(); 
    cout << "������� ������ �������� �� ���� ����� ��������!" << endl;
}

void sortByType(Source*& sources, size_t& count, const string& filename) {
    for (size_t i = 0; i < count - 1; i++) {
        for (size_t j = 0; j < count - i - 1; j++) {
            if (toLoweCase(sources[j].type.type) > toLoweCase(sources[j + 1].type.type)) {
                swap(sources[j], sources[j + 1]);
            }
        }
    }
    ofstream file(filename);
    if (!file.is_open()) {
        cout << "������� �������� ����� ��� ������!" << endl;
        return;
    }

    for (size_t i = 0; i < count; ++i) {
        if (toLoweCase(sources[i].type.type) != "�����") {
            sources[i].type.categore == "";
        }
        file << sources[i].type.type << "," << sources[i].title << "," << sources[i].author << "," << sources[i].year << "," << sources[i].type.categore << endl;
    }

    file.close();
    cout << "������!" << endl;

}
void sortByTitle(Source*& sources, size_t& count, const string& filename) {
    for (size_t i = 0; i < count - 1; i++) {
        for (size_t j = 0; j < count - i - 1; j++) {
            if (toLoweCase(sources[j].title) > toLoweCase(sources[j + 1].title)) {
                swap(sources[j], sources[j + 1]);
            }
        }
    }
    ofstream file(filename);
    if (!file.is_open()) {
        cout << "������� �������� ����� ��� ������!" << endl;
        return;
    }

    for (size_t i = 0; i < count; ++i) {
        if (toLoweCase(sources[i].type.type) != "�����") {
            sources[i].type.categore == "";
        }
        file << sources[i].type.type << "," << sources[i].title << "," << sources[i].author << "," << sources[i].year << "," << sources[i].type.categore << endl;
    }
    
    file.close();
    

}


void vybirkaKategory(Source*& sources, size_t& count,string category) {
    for (size_t i = 0; i < count; ++i) {
        if (toLoweCase(sources[i].type.type) == "�����") {
            if (toLoweCase(sources[i].type.categore) == toLoweCase(category)) {
                cout << "������: " << i << endl;
                cout << "���: " << sources[i].type.type << endl;
                cout << "�����: " << sources[i].title << endl;
                cout << "�����/��������: " << sources[i].author << endl;
                cout << "г� �������: " << sources[i].year << endl;
                cout << "�������� ������: " << sources[i].type.categore << endl;
                cout << "------------------------" << endl;
            }
            
        }
    }
}
void vybirkaAvtor(Source*& sources, size_t& count, string avtor) {
    for (size_t i = 0; i < count; ++i) {
        if (toLoweCase(sources[i].type.type) == "�����") {
            if (toLoweCase(sources[i].author) == toLoweCase(avtor)) {
                cout << "������: " << i << endl;
                cout << "���: " << sources[i].type.type << endl;
                cout << "�����: " << sources[i].title << endl;
                cout << "�����/��������: " << sources[i].author << endl;
                cout << "г� �������: " << sources[i].year << endl;
                cout << "�������� ������: " << sources[i].type.categore << endl;
                cout << "------------------------" << endl;
            }
 
        }
    }
}
void vybirkaRik(Source*& sources, size_t& count, string year) {
    for (size_t i = 0; i < count; ++i) {
        if (toLoweCase(sources[i].type.type) == "������") {
            if (sources[i].year == year) {
                cout << "������: " << i << endl;
                cout << "���: " << sources[i].type.type << endl;
                cout << "�����: " << sources[i].title << endl;
                cout << "�����/��������: " << sources[i].author << endl;
                cout << "г� �������: " << sources[i].year << endl;
                cout << "------------------------" << endl;
            }
           

        }
    }
}
void CountKategory(Source*& sources, size_t& count, string category) {
    int count1 = 0;
    string lowerCategory = toLoweCase(category);
    for (size_t i = 0; i < count; ++i) {
        if (toLoweCase(sources[i].type.type) == "�����") {
            if (toLoweCase(sources[i].type.categore) == lowerCategory) {
                count1 += 1;

            }

        }
    }
    cout << "ʳ������ ���� ������� " << category << " --> " << count1 << endl;
    cout << endl;
}


void removeGazete(Source*& sources, size_t& count, string year1, const string& filename) {
   
    int count1 = 0;
   
    for (size_t i = 0; i < count; ++i) {
        if (toLoweCase(sources[i].type.type) == "������") {
            if (toLoweCase(sources[i].year) == year1) {
                count1 += 1;

            }

        }
    }


    if (count1 == 0) {
        cout << "����� �� ����� " << year1 << " �� ��������." << endl;


    }
    int k = 0;
    Source* newSources = new Source[count - count1];
    for (size_t j = 0; j < count; ++j) {
        if (!(toLoweCase(sources[j].type.type) == "������" && sources[j].year == year1)) {
            newSources[k] = sources[j];
            k++;
        }
    }
    delete[] sources;
    sources = newSources;
    count -= count1;
    ofstream file(filename);
    if (!file.is_open()) {
        cout << "������� �������� ����� ��� ������!" << endl;
        return;
    }

    for (size_t i = 0; i < count; ++i) {
        if (toLoweCase(sources[i].type.type) != "�����") {
            sources[i].type.categore = "";  
        }
        file << sources[i].type.type << "," << sources[i].title << "," << sources[i].author << "," << sources[i].year << "," << sources[i].type.categore << endl;
           
           
           
      
    }


    file.close();

    
}




void vybirkaAvtorinazva(Source*& sources, size_t& count, string name, string avtor) {
    for (size_t i = 0; i < count; ++i) {
        if (toLoweCase(sources[i].type.type) == "�����") {
            if (toLoweCase(sources[i].author) == toLoweCase(avtor) && toLoweCase(sources[i].title) == toLoweCase(name)) {
                cout << "������: " << i << endl;
                cout << "���: " << sources[i].type.type << endl;
                cout << "�����: " << sources[i].title << endl;
                cout << "�����/��������: " << sources[i].author << endl;
                cout << "г� �������: " << sources[i].year << endl;
                cout << "�������� ������: " << sources[i].type.categore << endl;
                cout << "------------------------" << endl;
            }

        }
    }
}
void vybirkaZhurnal(Source*& sources, size_t& count, string name) {
    for (size_t i = 0; i < count; ++i) {
        if (toLoweCase(sources[i].type.type) == "������") {
            if (toLoweCase(sources[i].title) == toLoweCase(name)) {
                cout << "������: " << i << endl;
                cout << "���: " << sources[i].type.type << endl;
                cout << "�����: " << sources[i].title << endl;
                cout << "�����/��������: " << sources[i].author << endl;
                cout << "г� �������: " << sources[i].year << endl;
                cout << "�������� ������: " << sources[i].type.categore << endl;
                cout << "------------------------" << endl;
            }

        }
    }
}
int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    const string filename = "sources.txt"; 
    size_t capacity = 10;  
    size_t count = 0;     
    Source* sources = new Source[capacity];  


    loadSourcesFromFile(filename, sources, count, capacity);

  
    int choice;
    do {
        cout << "1. ��������� ���� �����" << endl;
        cout << "2. ����������� �� �������" << endl;
        cout << "3. ������ �� ���� �����" << endl;
        cout << "4. �������� �� �������" << endl;
        cout << "5. ������������� �� �����" << endl;
        cout << "6. �����" << endl;
        cout << "7. ������" << endl;
        cout << "8. ʳ������ ���� ����� �������" << endl;
        cout << "9. ��������� ������� ��� ������ �� ������ ��" << endl;



        cout << "0. �����" << endl;
        cout << "������� �����: ";
        cin >> choice;

        switch (choice) {
        case 1:
            int n1;
            cout << "����� ������� ����� ������: ";
            cin >> n1;
            addSource2(sources, count, capacity, filename, n1);
            cout << endl;
            break;
        case 2:
            viewSources(sources, count);
            cout << endl;
            break;
        case 3:
            addSource1(sources, count, capacity, filename);
            cout << endl;
            break;
        case 4:
            viewSources(sources, count);
            int in;
            cout << "����� �����: ";
            cin >> in;
            remove(sources, count, in, filename);
            cout << endl;
            break;

        case 5:
            int in1;
            cout << "������� �� ������ ��������� 1 - �� ����, 2 - �� ���� : ";
            cin >> in1;
            if (in1 == 1) {
                sortByTitle(sources, count, filename);
                viewSources(sources, count);
                cout << endl;
            }
            else if (in1 == 2) {
                sortByType(sources, count, filename);
                viewSources(sources, count);
                cout << endl;

            }
            else
            {
                cout << "�������(" << endl;
            }
            
            break;

        case 6: {
            int in23;
            cout << "�����: 1 - �������� ������ ����� (���� ����� � �����), 2 - �������� �������� �������: ";
            cin >> in23;
            if (in23 == 1) {
                string name;
                string author;
                cout << "����� ����� ����� : ";
                cin >> name;
                cout << "����� ������ ����� : ";
                cin >> author;
                vybirkaAvtorinazva(sources, count, name, author);
                cout << endl;
            }
            if (in23 == 2) {
                string name1;
          
                cout << "����� ����� ������� : ";
                cin >> name1;
             
                vybirkaZhurnal(sources, count, name1);
                cout << endl;
            }
            
            break;

        }
            
        case 7:
            int in2;
            cout << "������� �� ������ ������ 1 - ����� ������� �����, 2 - ����� ������� ������, 3 - ������ ������� ���� : ";
            cin >> in2;
            if (in2 == 1) {
                string in3;
                cout << "����� ������ ���� : ";
                cin >> in3;
                vybirkaKategory(sources, count, in3);
                cout << endl;
            }
            else if (in2 == 2) {
                string in4;
                cout << "����� ������� ������ : ";
                cin >> in4;
                vybirkaAvtor(sources, count, in4);
                cout << endl;
            }
            else if (in2 == 3) {
                string in5;
                cout << "����� �� �� ���� ������ �������� ������� : ";
                cin >> in5;
                vybirkaRik(sources, count, in5);
                cout << endl;
            }
            
            
            break;
        case 8: {
            string in�7;
            cout << "����� ������ ���� : ";
            cin >> in�7;
            CountKategory(sources, count, in�7);
            cout << endl;
            break;
        }
        case 9: {
            string in�8;
            cout << "����� �� ������: ";
            cin >> in�8;
            removeGazete(sources, count, in�8, filename);
            cout << endl;
            break;
        }
        case 0:
            cout << "����� � ��������." << endl;
            break;
        default:
            cout << "������������ ����, ��������� �� ���." << endl;
        }
    } while (choice != 0);

    delete[] sources;  
    return 0;
}