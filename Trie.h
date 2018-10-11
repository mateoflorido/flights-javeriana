//
// Created by mateo on 12/09/18.
//

#ifndef FLIGHTS_JAVERIANA_TRIE_H
#define FLIGHTS_JAVERIANA_TRIE_H

#include <string>

namespace FJA {
    class Trie {
    public:
        /**
         * @brief
         * @return
         */
        Trie *getNode();

        /**
         * @brief
         * @param root
         * @param key
         */
        void Insert(Trie *root, std::string key);

        /**
         * @brief
         * @param root
         * @param key
         * @return
         */
        bool Search(Trie *root, std::string key);

        /**
         * @brief
         * @param root
         * @return
         */
        bool IsLastNode(Trie *root);
        /**
         *
         * @param query
         * @return
         */
        std::string Coincidence(Trie *root, std::string &query, std::string &response);




    protected:
        Trie *Desc[26];
        bool isWordEnd;
    };
}


#endif //FLIGHTS_JAVERIANA_TRIE_H
