#include<iostream>
#include<fstream>
#include<vector>
#include<sstream>
#include<algorithm>

using namespace std;

struct videogame{
    string titolo;
    string piattaforma;
    string genere;
    int stato;
    string anno;
    string voto;
    int id;
};

string stato(int s)
{
    if(s == 0) return "da giocare";
    else if(s == 1) return "in corso";
    else return "completato";
}

void stampa_videogame(videogame vg){
    cout<<"ID: "<<vg.id<<endl;
    cout<<"Nome: "<<vg.titolo<<endl;
    cout<<"Piattaforma: "<<vg.piattaforma<<endl;
    cout<<"Genere: "<<vg.genere<<endl;
    cout<<"Stato: "<<stato(vg.stato)<<endl;
    cout<<"Anno: "<<vg.anno<<endl;
    cout<<"Voto: "<<vg.voto<<endl;
}

int generaId(vector<videogame> &vg)
{
    if (vg.empty())
        return 0;

    int maxId = vg[0].id;

    for (int i = 1; i < vg.size(); i++)
    {
        if (vg[i].id > maxId)
            maxId = vg[i].id;
    }

    return maxId + 1;
}

videogame creaGioco(vector<videogame> &vg)
{
    videogame vgNew;
    string temp;

    cout << "Titolo: ";
    getline(cin >> ws, vgNew.titolo);

    cout << "Piattaforma: ";
    getline(cin, vgNew.piattaforma);

    cout << "Genere: ";
    getline(cin, vgNew.genere);

    cout << "Anno: ";
    getline(cin, vgNew.anno);

    cout << "Voto: ";
    getline(cin, vgNew.voto);

    cout << "Stato (0/1/2): ";
    getline(cin, temp);
    vgNew.stato = stoi(temp);

    vgNew.id = generaId(vg);

    return vgNew;
}

void salvaFile(vector<videogame> &vg)
{
    ofstream file("videogiochi.txt");

    if (!file.is_open())
    {
        cout << "Errore apertura file" << endl;
        return;
    }

    file << vg.size() << endl;

    for (int i = 0; i < vg.size(); i++)
    {
        file << vg[i].id << "|"
             << vg[i].titolo << "|"
             << vg[i].genere << "|"
             << vg[i].piattaforma << "|"
             << vg[i].anno << "|"
             << vg[i].voto << "|"
             << vg[i].stato << endl;
    }

    file.close();
}

void stampa_menu(){
    cout<<"1. aggiungi un videogioco"<<endl;
    cout<<"2. informazioni sul tuo elenco"<<endl;
    cout<<"3. modifica di un videogioco in lista"<<endl;
    cout<<"4. elimina un videogioco dalla lista"<<endl;
}

void stampa_menu2_2(){
    cout<<"1. lista di tutti i giochi"<<endl;
    cout<<"2. ricerca di un videogioco per id o titolo"<<endl;
    cout<<"3. Filtro"<<endl;
    cout<<"4. top 5 videogiochi"<<endl;
}

void stampaTutto(vector<videogame> vg)
{
    sort(vg.begin(), vg.end(), [](const videogame &a, const videogame &b)
    {
        return a.titolo < b.titolo;
    });

    for (int i = 0; i < vg.size(); i++)
    {
        stampa_videogame(vg[i]);
        cout << endl;
    }
}
void classifica(vector<videogame> vg)
{
    if (vg.size() < 5)
    {
        cout << "Inserisci 5 o più giochi per fare la classifica." << endl;
        return;
    }

    for (int i = 0; i < vg.size(); i++)
    {
        for (int j = 0; j < vg.size() - i - 1; j++)
        {
            if (stoi(vg[j].voto) < stoi(vg[j + 1].voto))
            {
                swap(vg[j], vg[j + 1]);
            }
        }
    }

    cout << "Ecco la classifica dei top 5 giochi:" << endl;

    int limite = min(5, (int)vg.size());

    for (int i = 0; i < limite; i++)
    {
        cout << i + 1 << ") ";
        stampa_videogame(vg[i]);
        cout << endl;
    }
}
void deleteGame(vector<videogame> &vg)
{
    cout << "Inserisci l'ID del gioco che desideri eliminare: ";
    int scelta;
    cin >> scelta;

    for (int i = 0; i < vg.size(); i++)
    {
        if (vg[i].id == scelta)
        {
            vg.erase(vg.begin() + i);
            salvaFile(vg);
            cout << "Gioco eliminato con successo." << endl;
            return;
        }
    }

    cout << "ID non trovato." << endl;
}
void ricercaGiocoiD(vector<videogame> vg)
{
    cout << "Ricerca per ID (1) o per titolo (2)? ";

    int scelta;
    cin >> scelta;

    int rispostaId;
    string rispostaTit;

    if (scelta == 1)
    {
        cout << "Inserisci ID: ";
        cin >> rispostaId;

        for (int i = 0; i < vg.size(); i++)
        {
            if (vg[i].id == rispostaId)
            {
                stampa_videogame(vg[i]);
            }
        }
    }
    else if (scelta == 2)
    {
        cout << "Inserisci titolo: ";
        cin >> rispostaTit;

        for (int i = 0; i < vg.size(); i++)
        {
            if (vg[i].titolo == rispostaTit)
            {
                stampa_videogame(vg[i]);
            }
        }
    }
}

void filtro(vector<videogame> vg,int scelta)
{
    string valore;
    int st;

    if (scelta == 1)
    {
        cout << "Inserisci genere: ";
        cin >> valore;

        for (int i = 0; i < vg.size(); i++)
        {
            if (vg[i].genere == valore)
            {
                stampa_videogame(vg[i]);
                cout << endl;
            }
        }
    }
    else if (scelta == 2)
    {
        cout << "Inserisci piattaforma: ";
        cin >> valore;

        for (int i = 0; i < vg.size(); i++)
        {
            if (vg[i].piattaforma == valore)
            {
                stampa_videogame(vg[i]);
                cout << endl;
            }
        }
    }
    else if (scelta == 3)
    {
        cout << "Inserisci stato (0/1/2): ";
        cin >> st;

        for (int i = 0; i < vg.size(); i++)
        {
            if (vg[i].stato == st)
            {
                stampa_videogame(vg[i]);
                cout << endl;
            }
        }
    }
    else
    {
        cout << "Scelta non valida, reinserisci: ";
        int scelta1;
        cin >> scelta1;
        filtro(vg, scelta1);
    }
}

void scegliFiltro(vector<videogame> vg)
{
    int scelta;

    cout << "Vuoi filtrare per genere (1), piattaforma (2) o stato (3)? ";
    cin >> scelta;

    filtro(vg, scelta);
}
void updateGame(vector<videogame> &vg)
{
    cout << "Inserisci l'ID del gioco che desideri modificare: ";
    int scelta;
    cin >> scelta;

    for (int i = 0; i < vg.size(); i++)
    {
        if (vg[i].id == scelta)
        {
            cout << "Cosa vuoi modificare di questo videogioco?" << endl;
            cout << "TITOLO [1], GENERE [2], PIATTAFORMA [3], ANNO [4], VOTO [5], STATO [6], ESCI [0]: ";

            int decisione;
            cin >> decisione;

            string nuovo;
            int nuovo_stato;

            switch (decisione)
            {
                case 1:
                    cout << "Inserisci nuovo titolo: ";
                    getline(cin >> ws, nuovo);
                    vg[i].titolo = nuovo;
                    break;

                case 2:
                    cout << "Inserisci nuovo genere: ";
                    getline(cin >> ws, nuovo);
                    vg[i].genere = nuovo;
                    break;

                case 3:
                    cout << "Inserisci nuova piattaforma: ";
                    getline(cin >> ws, nuovo);
                    vg[i].piattaforma = nuovo;
                    break;

                case 4:
                    cout << "Inserisci nuovo anno: ";
                    getline(cin >> ws, nuovo);
                    vg[i].anno = nuovo;
                    break;

                case 5:
                    cout << "Inserisci nuovo voto: ";
                    getline(cin >> ws, nuovo);
                    vg[i].voto = nuovo;
                    break;

                case 6:
                    cout << "Inserisci nuovo stato (0/1/2): ";
                    cin >> nuovo_stato;
                    vg[i].stato = nuovo_stato;
                    break;

                case 0:
                    return;

                default:
                    cout << "Scelta non valida." << endl;
                    return;
            }

            salvaFile(vg);
            cout << "Videogioco aggiornato con successo." << endl;
            return;
        }
    }

    cout << "ID non trovato." << endl;
}
void azioneMenu2(int scelta, vector<videogame> &vg)
{
    if(scelta == 1)
    {
        stampaTutto(vg);
    }
    else if(scelta == 2)
    {
        ricercaGiocoiD(vg);
    }
    else if(scelta==3)
    {
        scegliFiltro(vg);
    }
    else if(scelta==4)
    {
        classifica(vg);
    }
    else
    {
        cout << "Errore rinserisci: ";
        int scelta1;
        cin >> scelta1;
        azioneMenu2(scelta1, vg);
    }
}

void azioneMenu1(int scelta, vector<videogame> &vg)
{
    if (scelta == 1)
    {
        vg.push_back(creaGioco(vg));
        salvaFile(vg);
    }
    else if (scelta == 2)
    {
        stampa_menu2_2();

        int scelta1;
        cin >> scelta1;

        azioneMenu2(scelta1, vg);
    }
    else if(scelta==3)
    {
        updateGame(vg);
    }
    else if(scelta==4)
    {
        deleteGame(vg);
    }
    else
    {
        int scelta2;
        cout<<"errore inserisci nuovamente la scelta: "<<endl;
        cin>>scelta2;
        azioneMenu1(scelta2,vg);

    }
}

int main()
{
    ifstream file("videogiochi.txt");

    if(!file.is_open()){
        cout<<"Errore file"<<endl;
        return 1;
    }

    vector<videogame> giochi;

    int n;
    file >> n;

    string riga;
    getline(file, riga);

    for(int i=0; i<n; i++)
    {
        videogame g;

        string id, st;

        getline(file, riga);
        stringstream ss(riga);

        getline(ss, id, '|');
        getline(ss, g.titolo, '|');
        getline(ss, g.genere, '|');
        getline(ss, g.piattaforma, '|');
        getline(ss, g.anno, '|');
        getline(ss, g.voto, '|');
        getline(ss, st);

        g.id = stoi(id);
        g.stato = stoi(st);

        giochi.push_back(g);
    }

    int scelta = 0;

    while (scelta != -1)
    {
        stampa_menu();
        cout << "Inserisci scelta (-1 per uscire): ";
        cin >> scelta;

        if (scelta != -1)
        {
            azioneMenu1(scelta, giochi);
        }
    }

    cout << "Uscita dal programma." << endl;

    return 0;
}