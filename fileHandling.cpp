#include<iostream>
#include<vector>
#include<sstream>
#include<fstream>
using namespace std;

class Examinee {
private:
    string id;
    float maths, lit, eng, phy, che, bio, his, geo, civ, natural, social;
public:
    Examinee();
    ~Examinee();
    Examinee readExaminee(string line_info);
    vector<Examinee> readList(string file_name);
    void writeTotal(string file_out_name, vector<Examinee> list);
    void enterScore(stringstream& ss, string temp, float& score);
};
Examinee::Examinee()
{

}

Examinee::~Examinee()
{

}

void Examinee::enterScore(stringstream& ss, string temp, float& score)
{
    getline(ss, temp, ',');
    if (temp.empty()) score = 0;
    else score = stof(temp);
}

Examinee Examinee::readExaminee(string line_info)
{
    stringstream ss;
    string temp;

    ss << line_info;
    getline(ss, id, ',');
    getline(ss, temp, ',');

    enterScore(ss, temp, maths);
    enterScore(ss, temp, lit);
    enterScore(ss, temp, phy);
    enterScore(ss, temp, che);
    enterScore(ss, temp, bio);
    enterScore(ss, temp, his);
    enterScore(ss, temp, geo);
    enterScore(ss, temp, civ);
    enterScore(ss, temp, natural);
    enterScore(ss, temp, social);
    enterScore(ss, temp, eng);

    return *this;
}

vector<Examinee> Examinee::readList(string file_name)
{
    vector<Examinee> list;
    stringstream ss;
    string temp;
    ifstream file;
    file.open(file_name,ifstream::in);
    getline(file, temp, '\n');
    while (getline(file, temp))
    {
        Examinee examTemp = readExaminee(temp);
        examTemp.natural = examTemp.phy + examTemp.che + examTemp.bio;
        examTemp.social = examTemp.his + examTemp.geo + examTemp.civ;
        list.push_back(examTemp);
    }
    file.close();
    return list;
}

void Examinee::writeTotal(string file_out_name, vector<Examinee> list)
{
    ofstream file(file_out_name, ofstream::out);
    float totalScore;

    for (int i = 0; i < list.size(); ++i)
    {
        totalScore = list[i].maths + list[i].lit + list[i].eng + list[i].natural + list[i].social;
        file << id << " " << totalScore << endl;
    }

    file.close();
}
int main()
{
    Examinee e;
    vector<Examinee> listResult;
    listResult = e.readList("data.txt");
    e.writeTotal("dataOutput.txt", listResult);
    return 0;
}