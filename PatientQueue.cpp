#include <iostream> 
#include <fstream>
#include <string>

using namespace std;

// Hastalarin bilgilerini dugumde tutucaz.
struct Node {
    string ad, soyad;
    long long int tc;  // normal int tipi deðiþken maksimum 9 rakamli ola bildiðinden 2^63-1 e kadar deger tuta bilen long long int kullandik.

    Node* next;
    // Dugumu yaratirken direk atama yapa bilmek için yazdik.
    Node(long long int t, string a, string s)
    {
        tc = t;
        ad = a;
        soyad = s;
        next = NULL;
    }
};


struct Queue {
    // Kuyrugun onunu ve arkasini yaratiyoruz ve NULL yapiyoruz.
    Node* front, * rear;
    Queue()
    {
        front = rear = NULL;
    }

    void HastaEkle()    // Siraya adam ekleme 
    {
        ofstream fout; // Dosyayi yazma modunda açiyoruz.
        

        // Kullanicidan hasta bilgilerini aliyoruz.
        string ad, soyad;
        long long int tc;

        cout << endl << endl << "Hasta Adi:  ";
        cin >> ad;

        cout << "Hasta Soyadi:  ";
        cin >> soyad;

        cout << "Hasta TC:  ";
        cin >> tc;


        // Aldiðimiz bilgilerle yeni Hasta yaratiyoruz. 
        Node* temp = new Node(tc, ad, soyad);

        // Eger kuyruk boþsa yeni hasta kuyruðun hem baþi hemde sonu oluyor ve yeni dosya yaratip içine hasta bilgilerini yaziyoruz.
        // Ama kuyruk bos degilse dosyanin sonuna bilgileri yaziyoruz.
        if (rear == NULL) {
            fout.open("Hasta.txt");
            fout << tc << " |" << ad << " " << soyad <<  endl;
            front = rear = temp;
            return;
        }
        else
        {
            fout.open("Hasta.txt", ios::app);
            fout << tc << " |" << ad << " " << soyad <<  endl;
        }



        // Yeni dugumu kuyrugun sonuna ekleyip sonu yeni dugum olacak sekilde degisiyoruz. 
        rear->next = temp;
        rear = temp;

        fout.close(); 

    }

    void ilk_satiri_sil()
    {
        // Dosyayi okuma modunda aciyoruz. 
        ifstream is("Hasta.txt");

        // Dosyayi yazma modunda aciyoruz. 
        ofstream ofs;
        ofs.open("temp.txt", ofstream::out);

        // Donguyle tek tek karekterleri aliyoruz
        char c;
        int line_no = 1;
        while (is.get(c))
        {

            // Eger ilk satirdaysak yazdirmiyoruz aksi halde yazdiriyoruz.
            if (line_no != 1)
                ofs << c;

            // Her yeni satirda satir numarasini artiriyoruz.
            if (c == '\n')
                line_no++;
        }

        ofs.close();    // Dosyalari kapatiyoruz.
        is.close();

        // Orjinal dosyayi siliyoruz 
        remove("Hasta.txt");

        // temp dosyasinin adini degisiyoruz.
        rename("temp.txt", "Hasta.txt");
    }

    // Kuyruktan adam silme
    void HastaSil() 
    {        
        // Eger kuyruk boþsa NULL donderiyoruz. 
        if (front == NULL)
            return;


        // En ondeki dugumu bir degiþkende saklayip front-u degisiyoruz.
        Node* temp = front;
        front = front->next;

        // Eger yukardaki islem sonrasi front NULL olursa rear-ýda NULL yapiyoruz.
        if (front == NULL)
            rear = NULL;

        ilk_satiri_sil();   // Ilk satiri siliyoruz.
        cout << endl << temp->ad << " " << temp->soyad << " doktorun yaninda. " << endl;
        delete (temp);
        
    }

    void Listele()
    {
        string line;
        ifstream fin;

        fin.open("Hasta.txt");

        if (fin) cout << endl << endl << "TC          | Isim Soyisim " <<
                                endl << "------------|---------------------" << endl;

        else cout << endl << "Kayit Bulunmamakta.";

        while (fin) {

            getline(fin, line);

            cout << line << endl;
        }

        fin.close();
    }

  
};
 
int main()
{

    Queue q;
    string* options = new string[4]{    "1. Siraya Hasta Ekle" , 
                                        "2. Siradan Hasta Al", 
                                        "3. Sirayi Listele", 
                                        "4. Programi Bitir"     };
    int option = 0;

    cout << "||||||||| Hasta Sira Sistemi |||||||||" << endl << endl;


    while (option != 4) {

        cout << endl << endl    << options[0] << endl 
                                << options[1] << endl 
                                << options[2] << endl 
                                << options[3] << endl 
                                << endl << "Seciminiz: ";

        cin >> option;
    
        switch (option)
        {
            case 1:
                q.HastaEkle();
                break;
            case 2:
                q.HastaSil();
                break;
            case 3:
                q.Listele();
                break;
            case 4:
                break;
            default:
                cout << "Yanlis Girdiniz" << endl;
                break;
        }
    }

    return 0;
}