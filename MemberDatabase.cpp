//
//  MemberDatabase.cpp
//  unhingedp4
//
//  Created by Geoffrey  Xu on 3/3/22.
//

#include "MemberDatabase.h"

MemberDatabase::MemberDatabase()
{
}

MemberDatabase::~MemberDatabase()
{
    for (int i = 0; i < m_people.size(); i++)
    {
        delete m_people[i];
    }
    m_people.clear();
}

bool MemberDatabase::LoadDatabase(string filename)
{
    ifstream file(filename);
    if (!file) {
        return false;
    }
    string email, name, attribute, value, ignore;
    int count = 0;
    while (file.good())
    {
        getline(file, name);
        getline(file, email);
        if (member_tree.search(email) != nullptr) {
            return false;
        }
        file >> count;
        getline(file, ignore);
        PersonProfile* newPerson = new PersonProfile(name, email);
        m_people.push_back(newPerson);
        for (int i = 0; i < count; i++)
        {
            getline(file, attribute, ',');
            getline(file, value);
            string attVals = attribute + value;
            newPerson->AddAttValPair(AttValPair(attribute, value));
            vector<string> toInsert;
            if (m_emailsToKeys.search(attVals) == nullptr)
            {
                toInsert.push_back(email);
                m_emailsToKeys.insert(attVals, toInsert);
            }
            else
            {
                m_emailsToKeys.search(attVals)->push_back(email);
            }
        }
        /*for (int i = 0; i < count; i++)
        {
            getline(file, attribute, ',');
            getline(file, value);
            string attVals = attribute + value;
            vector<string>** emails = m_emails.search(attVals);
            if (m_emails.search(attVals) == nullptr)
            {
                m_emails.insert(attVals, new vector<string>);
                emails = m_emails.search(attVals);
            }
            (*emails)->push_back(attVals);
            newPerson->AddAttValPair(AttValPair(attribute, value));
        }*/
        getline(file, ignore);
        member_tree.insert(email, newPerson);
    }
    return true;
}

vector<string> MemberDatabase::FindMatchingMembers(const AttValPair& input) const
{
    string attVals = input.attribute + input.value;
    return (*m_emailsToKeys.search(attVals));
}

const PersonProfile* MemberDatabase::GetMemberByEmail(string email) const
{
    if (member_tree.search(email) == nullptr)
        return nullptr;
    return (*member_tree.search(email));
}

