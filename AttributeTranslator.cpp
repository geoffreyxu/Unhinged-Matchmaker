//
//  AttributeTranslator.cpp
//  unhingedp4
//
//  Created by Geoffrey  Xu on 3/3/22.
//

#include "AttributeTranslator.h"

AttributeTranslator::AttributeTranslator()
{
}

AttributeTranslator::~AttributeTranslator() {}

bool AttributeTranslator::Load(string filename)
{
    string data1, data2, encode1, encode2;
    ifstream file(filename);
    if (!file)
        return false;
    while (file.good())
    {
        getline(file, data1, ',');
        getline(file, data2, ',');
        getline(file, encode1, ',');
        getline(file, encode2);
        string data = data1 + data2;
        string encode = encode1 + encode2;
        AttValPair a(encode1, encode2);
        AttValPair b(data1, data2);
        data2 = "";
        data1 = "";
        encode1 = "";
        encode2 = "";
        vector<AttValPair> toInsert;
        vector<AttValPair> toInsert1;

        // unordered_set<string> toInsert;
        /*toInsert.insert(encode);
        if (m_compatibles.search(data) == nullptr)
        {
            m_compatibles.insert(data, toInsert);
        }
        else
            m_compatibles.search(data)->insert(encode); */
        if (data == ",")
            return true;
        if (m_compatibles.search(data) == nullptr)
        {
            toInsert.push_back(a);
            m_compatibles.insert(data, toInsert);
        }
        else if (m_compatibles.search(data) != nullptr)
            m_compatibles.search(data)->push_back(a);
        if (m_compatibles.search(encode) == nullptr)
        {
            toInsert1.push_back(b);
            m_compatibles.insert(encode, toInsert1);
        }
        else if (m_compatibles.search(data) != nullptr)
            m_compatibles.search(encode)->push_back(b);
        /* string datum = data.substr(size + 1,data.size() - 1);
        size_t cutoff = datum.find(',');
        if (compatibles->search(encode) == nullptr)
        {
            vector<AttValPair> v;
            compatibles->insert(encode, v);
            v.push_back((AttValPair(datum.substr(0, cutoff), datum.substr(cutoff + 1, datum.size()-1))));
        }
        else
        {
            compatibles->search(encode)->push_back((AttValPair(datum.substr(0, cutoff), datum.substr(cutoff + 1, datum.size()-1))));
            attributeValues.erase(compatibles->search(encode));
        }
        attributeValues.insert(compatibles->search(encode));*/
    }
    return true;
}

vector<AttValPair> AttributeTranslator::FindCompatibleAttValPairs(const AttValPair& source) const
{
    string key = source.attribute + source.value;
    vector<AttValPair> v;
    if (m_compatibles.search(key) == nullptr)
        return v;
    /* v = *m_compatibles.search(key);
    for (int i = 0; i < v.size(); i++)
    {
        cout << v[i].attribute << v[i].value << endl;
    }*/
    return *m_compatibles.search(key);
}
