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
 
        if (str[i] >= 'А' && str[i] <= 'Я') {
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
        cout << "Помилка відкриття файлу для запису!" << endl;
        return;
    }
    if (toLoweCase(source.type.type) != "книга") {
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


    cout << "Введіть тип джерела (книга, журнал, газета): ";
    cin >> sources[count].type.type;
    cin.ignore(); 
    cout << "Введіть назву: ";
    getline(cin, sources[count].title);
    cout << "Введіть автора/видавця: ";
    getline(cin, sources[count].author);
    cout << "Введіть рік видання: ";
    getline(cin, sources[count].year);
    if (toLoweCase(sources[count].type.type) == "книга") {
        cout << "Введіть категорію книжки: ";
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
        cout << "Введіть тип джерела (книга, журнал, газета): ";
        cin >> sources[count].type.type;
        cin.ignore();
        cout << "Введіть назву: ";
        getline(cin, sources[count].title);
        cout << "Введіть автора/видавця: ";
        getline(cin, sources[count].author);
        cout << "Введіть рік видання: ";
        getline(cin, sources[count].year);
        if (toLoweCase(sources[count].type.type) == "книга") {
            cout << "Введіть категорію книжки: ";
            getline(cin, sources[count].type.categore);
        }

        saveSourceToFile(filename, sources[count]);
        ++count;
    }
    

}
 


void viewSources(Source* sources, size_t count) {
    if (count == 0) {
        cout << "База даних порожня." << endl;
        return;
    }

    cout << "Джерела в базі даних:" << endl;
    cout << "========================" << endl;
    for (size_t i = 0; i < count; ++i) {
        cout << "Індекс: " << i << endl;
        cout << "Тип: " << sources[i].type.type << endl;
        cout << "Назва: " << sources[i].title << endl;
        cout << "Автор/Видавець: " << sources[i].author << endl;
        cout << "Рік видання: " << sources[i].year << endl;
        if (sources[i].type.type == "книга" or sources[i].type.type == "Книга")
            cout << "Категорія книжки: " << sources[i].type.categore << endl;
    
        cout << "------------------------" << endl;
    }
}


void loadSourcesFromFile(const string& filename, Source*& sources, size_t& count, size_t& capacity) {
    ifstream file(filename);
    if (!file.is_open()) {
        cout << "Помилка відкриття файлу для читання!" << endl;
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
        cout << "Помилка відкриття файлу для запису!" << endl;
        return;
    }

    for (size_t i = 0; i < count; ++i) {
        if (toLoweCase(sources[i].type.type) != "книга") {
            sources[i].type.categore == "";
        }
        file << sources[i].type.type << "," << sources[i].title << "," << sources[i].author << "," << sources[i].year << "," << sources[i].type.categore << endl;
    }

    file.close(); 
    cout << "Джерело успішно видалено та база даних оновлена!" << endl;
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
        cout << "Помилка відкриття файлу для запису!" << endl;
        return;
    }

    for (size_t i = 0; i < count; ++i) {
        if (toLoweCase(sources[i].type.type) != "книга") {
            sources[i].type.categore == "";
        }
        file << sources[i].type.type << "," << sources[i].title << "," << sources[i].author << "," << sources[i].year << "," << sources[i].type.categore << endl;
    }

    file.close();
    cout << "Успішно!" << endl;

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
        cout << "Помилка відкриття файлу для запису!" << endl;
        return;
    }

    for (size_t i = 0; i < count; ++i) {
        if (toLoweCase(sources[i].type.type) != "книга") {
            sources[i].type.categore == "";
        }
        file << sources[i].type.type << "," << sources[i].title << "," << sources[i].author << "," << sources[i].year << "," << sources[i].type.categore << endl;
    }
    
    file.close();
    

}


void vybirkaKategory(Source*& sources, size_t& count,string category) {
    for (size_t i = 0; i < count; ++i) {
        if (toLoweCase(sources[i].type.type) == "книга") {
            if (toLoweCase(sources[i].type.categore) == toLoweCase(category)) {
                cout << "Індекс: " << i << endl;
                cout << "Тип: " << sources[i].type.type << endl;
                cout << "Назва: " << sources[i].title << endl;
                cout << "Автор/Видавець: " << sources[i].author << endl;
                cout << "Рік видання: " << sources[i].year << endl;
                cout << "Категорія книжки: " << sources[i].type.categore << endl;
                cout << "------------------------" << endl;
            }
            
        }
    }
}
void vybirkaAvtor(Source*& sources, size_t& count, string avtor) {
    for (size_t i = 0; i < count; ++i) {
        if (toLoweCase(sources[i].type.type) == "книга") {
            if (toLoweCase(sources[i].author) == toLoweCase(avtor)) {
                cout << "Індекс: " << i << endl;
                cout << "Тип: " << sources[i].type.type << endl;
                cout << "Назва: " << sources[i].title << endl;
                cout << "Автор/Видавець: " << sources[i].author << endl;
                cout << "Рік видання: " << sources[i].year << endl;
                cout << "Категорія книжки: " << sources[i].type.categore << endl;
                cout << "------------------------" << endl;
            }
 
        }
    }
}
void vybirkaRik(Source*& sources, size_t& count, string year) {
    for (size_t i = 0; i < count; ++i) {
        if (toLoweCase(sources[i].type.type) == "журнал") {
            if (sources[i].year == year) {
                cout << "Індекс: " << i << endl;
                cout << "Тип: " << sources[i].type.type << endl;
                cout << "Назва: " << sources[i].title << endl;
                cout << "Автор/Видавець: " << sources[i].author << endl;
                cout << "Рік видання: " << sources[i].year << endl;
                cout << "------------------------" << endl;
            }
           

        }
    }
}
void CountKategory(Source*& sources, size_t& count, string category) {
    int count1 = 0;
    string lowerCategory = toLoweCase(category);
    for (size_t i = 0; i < count; ++i) {
        if (toLoweCase(sources[i].type.type) == "книга") {
            if (toLoweCase(sources[i].type.categore) == lowerCategory) {
                count1 += 1;

            }

        }
    }
    cout << "Кількість книг категорії " << category << " --> " << count1 << endl;
    cout << endl;
}


void removeGazete(Source*& sources, size_t& count, string year1, const string& filename) {
   
    int count1 = 0;
   
    for (size_t i = 0; i < count; ++i) {
        if (toLoweCase(sources[i].type.type) == "газета") {
            if (toLoweCase(sources[i].year) == year1) {
                count1 += 1;

            }

        }
    }


    if (count1 == 0) {
        cout << "Газет із роком " << year1 << " не знайдено." << endl;


    }
    int k = 0;
    Source* newSources = new Source[count - count1];
    for (size_t j = 0; j < count; ++j) {
        if (!(toLoweCase(sources[j].type.type) == "газета" && sources[j].year == year1)) {
            newSources[k] = sources[j];
            k++;
        }
    }
    delete[] sources;
    sources = newSources;
    count -= count1;
    ofstream file(filename);
    if (!file.is_open()) {
        cout << "Помилка відкриття файлу для запису!" << endl;
        return;
    }

    for (size_t i = 0; i < count; ++i) {
        if (toLoweCase(sources[i].type.type) != "книга") {
            sources[i].type.categore = "";  
        }
        file << sources[i].type.type << "," << sources[i].title << "," << sources[i].author << "," << sources[i].year << "," << sources[i].type.categore << endl;
           
           
           
      
    }


    file.close();

    
}




void vybirkaAvtorinazva(Source*& sources, size_t& count, string name, string avtor) {
    for (size_t i = 0; i < count; ++i) {
        if (toLoweCase(sources[i].type.type) == "книга") {
            if (toLoweCase(sources[i].author) == toLoweCase(avtor) && toLoweCase(sources[i].title) == toLoweCase(name)) {
                cout << "Індекс: " << i << endl;
                cout << "Тип: " << sources[i].type.type << endl;
                cout << "Назва: " << sources[i].title << endl;
                cout << "Автор/Видавець: " << sources[i].author << endl;
                cout << "Рік видання: " << sources[i].year << endl;
                cout << "Категорія книжки: " << sources[i].type.categore << endl;
                cout << "------------------------" << endl;
            }

        }
    }
}
void vybirkaZhurnal(Source*& sources, size_t& count, string name) {
    for (size_t i = 0; i < count; ++i) {
        if (toLoweCase(sources[i].type.type) == "журнал") {
            if (toLoweCase(sources[i].title) == toLoweCase(name)) {
                cout << "Індекс: " << i << endl;
                cout << "Тип: " << sources[i].type.type << endl;
                cout << "Назва: " << sources[i].title << endl;
                cout << "Автор/Видавець: " << sources[i].author << endl;
                cout << "Рік видання: " << sources[i].year << endl;
                cout << "Категорія книжки: " << sources[i].type.categore << endl;
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
        cout << "1. Заповнити базу даних" << endl;
        cout << "2. Переглянути всі джерела" << endl;
        cout << "3. Додати до бази даних" << endl;
        cout << "4. Видалити по індексу" << endl;
        cout << "5. Упорядкування по полях" << endl;
        cout << "6. Пошук" << endl;
        cout << "7. Вибірка" << endl;
        cout << "8. Кількість книг деякої категорії" << endl;
        cout << "9. Видалення зведень про газети за певний рік" << endl;



        cout << "0. Вийти" << endl;
        cout << "Виберіть опцію: ";
        cin >> choice;

        switch (choice) {
        case 1:
            int n1;
            cout << "Ведіть кількість нових записів: ";
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
            cout << "Ведіть ідекс: ";
            cin >> in;
            remove(sources, count, in, filename);
            cout << endl;
            break;

        case 5:
            int in1;
            cout << "Виберіть як хочете сортувати 1 - по назві, 2 - по типу : ";
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
                cout << "Помилка(" << endl;
            }
            
            break;

        case 6: {
            int in23;
            cout << "Пошук: 1 - наявність заданої книги (відомі автор і назва), 2 - наявність заданого журналу: ";
            cin >> in23;
            if (in23 == 1) {
                string name;
                string author;
                cout << "Ведіть назву книги : ";
                cin >> name;
                cout << "Ведіть автора книги : ";
                cin >> author;
                vybirkaAvtorinazva(sources, count, name, author);
                cout << endl;
            }
            if (in23 == 2) {
                string name1;
          
                cout << "Ведіть назву журнала : ";
                cin >> name1;
             
                vybirkaZhurnal(sources, count, name1);
                cout << endl;
            }
            
            break;

        }
            
        case 7:
            int in2;
            cout << "Виберіть як хочете вибірка 1 - книга певного жанру, 2 - книга певного автора, 3 - журнал певного року : ";
            cin >> in2;
            if (in2 == 1) {
                string in3;
                cout << "Ведіть певний жанр : ";
                cin >> in3;
                vybirkaKategory(sources, count, in3);
                cout << endl;
            }
            else if (in2 == 2) {
                string in4;
                cout << "Ведіть певного автора : ";
                cin >> in4;
                vybirkaAvtor(sources, count, in4);
                cout << endl;
            }
            else if (in2 == 3) {
                string in5;
                cout << "Ведіть рік за який хочете побачити журнали : ";
                cin >> in5;
                vybirkaRik(sources, count, in5);
                cout << endl;
            }
            
            
            break;
        case 8: {
            string inі7;
            cout << "Ведіть певний жанр : ";
            cin >> inі7;
            CountKategory(sources, count, inі7);
            cout << endl;
            break;
        }
        case 9: {
            string inі8;
            cout << "Ведіть рік книжки: ";
            cin >> inі8;
            removeGazete(sources, count, inі8, filename);
            cout << endl;
            break;
        }
        case 0:
            cout << "Вихід з програми." << endl;
            break;
        default:
            cout << "Неправильний вибір, спробуйте ще раз." << endl;
        }
    } while (choice != 0);

    delete[] sources;  
    return 0;
}