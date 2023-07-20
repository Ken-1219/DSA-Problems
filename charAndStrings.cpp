#include "bits/stdc++.h"
using namespace std;

int getLength(char str[])
{
  int i = 0;
  int count = 0;

  while (str[i] != '\0')
    {
      count++;
      i++;
    }
  return count;
}

void reverseCharArray(char str[])
{
  int i = 0, j = getLength(str) - 1;

  while (i <= j)
    {
      swap(str[i++], str[j--]);
    }
}

char toLowerCase(char ch)
{
  if ((ch >= 'a' && ch <= 'z') || (ch >= '0' && ch <= '9'))
    {
      return ch;
    }
  else
    {
      char temp = ch - 'A' + 'a';
      return temp;
    }
}


//it makes string not case sensitive

// bool checkPalindrome(char str[])
// {
//   int i = 0, j = getLength(str) - 1;

//   while (i <= j)
//     {
//       if (toLowerCase(str[i]) != toLowerCase(str[j]))
//         {
//           return false;
//         }
//       i++; j--;
//     }
//   return true;
// }


bool validCharacter(char ch)
{
  if ((ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z') || (ch >= '0' && ch <= '9'))
    {
      return true;
    }
  return false;
}


//string can contain special characters too ->  special characters will be ignored and only alphanumeric characters will be considered

bool checkPalindrome(string s)
{
  string temp = "";

  for (int j = 0; j < s.length(); j++)
    {
      if (validCharacter(s[j]))
        {
          temp.push_back(s[j]);
        }
    }

  for (int i = 0; i < temp.length(); i++)
    {
      temp[i] = toLowerCase(temp[i]);
    }

  int st = 0, e = temp.length() - 1;

  while (st <= e)
    {
      if (temp[st] != temp[e])
        {
          return false;
        }
      st++;
      e--;
    }
  return true;
}

//Reverse Words in  a string
/*
   You are given a string with words separated by spaces within it.
   For eg.: "My name is Mohit"
   You have to reverse each word in the given string
   Output: "yM eman si tihoM"
 */

string reverseString(string str)
{
  int i = 0, j = str.length() - 1;

  while (i <= j)
    {
      swap(str[i++], str[j--]);
    }
  return str;
}

string reverseWordsInString(string s)
{
  string str = "";
  string temp = "";

  for (int i = 0; i < s.length(); ++i)
    {
      if (s[i] == ' ' || s[i] == '\0')
        {
          temp = reverseString(temp);
          str.append(temp);
          str.push_back(' ');
          temp = "";
        }
      else
        {
          temp.push_back(s[i]);
        }
    }

//last word will remain in temp and will not be appended so has to append separately

  temp = reverseString(temp);
  str.append(temp);
  str.push_back(' ');
  return str;
}


string replaceSpaces(string &str)
{
  int space_count = 0;

  for (int i = 0; i < str.length(); ++i)
    {
      if (str[i] == ' ')
        {
          space_count++;
        }
    }

  // int new_length = str.length() + space_count * 2 - 1;
  int new_length = 25;

  int index = new_length - 1;
  for (int j = str.length() - 1 ; j >= 0 ; j--)
    {
      if (str[j] == ' ')
        {
          cout << "-----space encountered-----" << endl;
          str[index] = '0';
          str[index - 1] = '4';
          str[index - 2] = '@';
          index = index - 3;
          cout << "----replacement done----" << endl;
        }
      else
        {
          str[index] = str[j];
          cout << "No space encountered" << endl;
          index--;
        }
    }
  cout << "---everything is done---" << endl;
  return str;
}




int main()
{
  string str;

  getline(cin, str);

  str = replaceSpaces(str);
  cout << "function called" << endl;
  cout << str << endl;

  return 0;
}