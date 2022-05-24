#ifndef EX5_PARTA_ORGCHART_H
#define EX5_PARTA_ORGCHART_H

#endif //EX5_PARTA_ORGCHART_H
#include <iostream>
#include <vector>
#include <list>

#pragma once

using namespace std;

namespace ariel{

    class OrgChart {
    public:

        typedef struct Node{
            string _value;
            Node* _next;
            bool _visited;
            vector<Node*> _children;
        }Node;


    private:
        Node* _root;
        Node* _tail;
        vector<Node*> _allNodes;
        vector<Node*> _preOrder;
    public:
        OrgChart():_root(nullptr),_tail(nullptr),_preOrder(),_allNodes(){
            cout<< "OrgChart was created"<<endl;
        }
        OrgChart(const OrgChart &other){
            for (unsigned int i = 0; i < other._allNodes.size(); ++i) {
                Node* temp = new Node();
                temp->_value = other._allNodes.at(i)->_value;
                this->_allNodes.push_back(temp);
            }
            if(other._root == NULL){
                this->_root = NULL;
            }
            else{
                this->_root = this->_allNodes.at(0);
            }
        }
        ~OrgChart(){
            for(Node* n: this->_allNodes){
                n->_next= nullptr;
                cout<< "delete node number "<< n->_value<<endl;
                delete n;
            }

        }
        OrgChart& add_root(const string& root);
        OrgChart& add_sub(const string& root,const string& child );
        friend ostream& operator<<(ostream& out, const OrgChart& OrgChart);
        void BFS();
        void revBFS();
        void DFS();
        void DFS_Visit(Node* curr);

        //inner class LevelIterator:
        class OrgChartIterator {
        private:
            Node* _current_node;


        public:
            OrgChartIterator(Node* ptr = nullptr): _current_node(ptr) {
            }
            ~OrgChartIterator(){}

            Node* operator&(){
                return _current_node;
            }

            string& operator*() const {
                //return *pointer_to_current_node;
                return _current_node->_value;
            }

            string* operator->() const {
                return &(_current_node->_value);
            }

            // ++i;
            OrgChartIterator& operator++() {
                //++pointer_to_current_node;
                _current_node = _current_node->_next;
                return *this;
            }

            // i++;
            // Usually iterators are passed by value and not by const& as they are small.
            const OrgChartIterator operator++(int) {
                OrgChartIterator tmp= *this;
                _current_node= _current_node->_next;
                return tmp;
            }

            bool operator==(const OrgChartIterator& rhs) const {
                return _current_node == rhs._current_node;
            }

            bool operator!=(const OrgChartIterator& node) const {
                return _current_node != node._current_node;
            }
        };  // END OF CLASS OrgChartIterator


        OrgChartIterator begin_level_order(){
            if (_allNodes.empty()){
                throw invalid_argument("The orgChart is empty!");
            }
            this->BFS();
            return OrgChartIterator{_root};
        }
        OrgChartIterator end_level_order(){
            if (_allNodes.empty()){
                throw invalid_argument("The orgChart is empty!");
            }
            return nullptr;
        }

        OrgChartIterator begin_reverse_order(){
            if (_allNodes.empty()){
                throw invalid_argument("The orgChart is empty!");
            }
            this->revBFS();
            return OrgChartIterator{_tail}; // should be replaced because we iterate from the end of the OrgChart.
        }

        OrgChartIterator reverse_order(){
            if (_allNodes.empty()){
                throw invalid_argument("The orgChart is empty!");
            }
            return nullptr;
        }

        OrgChartIterator begin_preorder(){
            if (_allNodes.empty()){
                throw invalid_argument("The orgChart is empty!");
            }
            _preOrder.clear();
            this->DFS();
            for (size_t i = 0; i <_preOrder.size()-1 ; ++i) {
                _preOrder.at(i)->_next = _preOrder.at(i+1);
            }
            _preOrder.at(_preOrder.size() - 1)->_next = nullptr;
            return OrgChartIterator{_root};
        }

        OrgChartIterator end_preorder(){
            if (_allNodes.empty()){
                throw invalid_argument("The orgChart is empty!");
            }
            return nullptr;
        }

        OrgChartIterator begin(){
            if (_allNodes.empty()){
                throw invalid_argument("The orgChart is empty!");
            }
            this->BFS();
            return OrgChartIterator{_root};
        }
        OrgChartIterator end(){
            if (_allNodes.empty()){
                throw invalid_argument("The orgChart is empty!");
            }
            return nullptr;
        }

    };
}

