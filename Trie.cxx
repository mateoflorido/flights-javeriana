//
// Created by mateo on 14/10/18.
//

#include "Trie.h"

//---------------------------------------------------------------------------------
FJA::Trie::TrieNode::
TrieNode() {
  this->End = false;
  for (auto i = 0; i < 26; i++) {
    this->children[i] = nullptr;
  }
}

//---------------------------------------------------------------------------------
void FJA::Trie::TrieNode::
Insert(const std::string &v) {
  TrieNode *actual = this;
  for (auto i = 0; i < v.length(); i++) {
    auto index = v[i] - 'a';
    if (actual->children[index] == nullptr)
      actual->children[index] = new TrieNode();
    actual = actual->children[index];
  }

  actual->End = true;

}

//--------------------------------------------------------------------------------
bool FJA::Trie::TrieNode::
Search(const std::string &v) {
  TrieNode *actual = this;
  for (auto i = 0; i < v.length(); i++) {
    auto index = v[i] - 'a';
    if (actual->children[index] == nullptr)
      return false;
    actual = actual->children[index];
  }

  return (actual != nullptr && actual->End);
}
//--------------------------------------------------------------------------------
bool FJA::Trie::TrieNode::
Last() {
  for (auto i = 0; i < 26; i++) {
    if (this->children[i] != nullptr)
      return false;
  }
  return true;
}

//--------------------------------------------------------------------------------
std::string FJA::Trie::TrieNode::
Coincidence(const std::string &query, std::string &r) {
  TrieNode *actual = this;
  for (auto i = 0; i < query.length(); i++) {
    auto index = query[i] - 'a';
    if (actual->children[index] == nullptr) {
      r.clear();
      return r;
    } else
      r += query[i];
    actual = actual->children[index];
  }
  while (!actual->End) {
    for (auto i = 0; i < 26; i++) {
      if (actual->Last())
        return r;
      if (actual->children[i] != nullptr) {
        r += (char) ('a' + i);
        actual = actual->children[i];
        break;
      }
    }
  }
  return r;
}

//--------------------------------------------------------------------------------
FJA::Trie::Trie() {
  this->m_Root = new TrieNode();
}
//--------------------------------------------------------------------------------
void FJA::Trie::
Insert(const std::string &v) {
  if (this->m_Root != nullptr) {
    this->m_Root->Insert(v);
  }
}
//--------------------------------------------------------------------------------
bool FJA::Trie::
Search(const std::string &v) {
  if (this->m_Root != nullptr) {
    this->m_Root->Search(v);
  } else
    return false;
}
//--------------------------------------------------------------------------------
std::string FJA::Trie::
Coincidence(const std::string &query, std::string &r) {
  if (this->m_Root != nullptr) {
    this->m_Root->Coincidence(query, r);
    return r;
  } else
    return "";
}