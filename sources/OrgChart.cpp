#include <iostream>
#include "OrgChart.hpp"


using namespace std;


namespace ariel{
    OrgChart& OrgChart::add_root(const string& root){
        if (_root == nullptr){ // there is no root
            _root= new Node();
            _root->_value=root;
            _allNodes.push_back(_root);
        }
        else{
            cout<< "there is root so i replace him" << endl;
            _root->_value = root;
        }
        return *this;
    }
    OrgChart& OrgChart::add_sub(const string& root,const string& child ){
        for (auto it = this->begin_level_order(); it != this->end_level_order(); ++it)
        {
            if ((*it) == root){
                Node* curr = (&it);
                Node* new_node = new Node();
                new_node->_value = child;
                curr->_children.push_back(new_node);
                _allNodes.push_back(new_node);
                return *this;
            }
        }
        // there is no Node("root") in the OrgChart
        throw invalid_argument("There is no such Node 'root' in the OrgChart");
    }
    ostream& operator<<(ostream &out, const OrgChart& Orgchart){

        return out;
    }

    void OrgChart::BFS(){
        for (size_t i = 0; i < _allNodes.size() ; ++i) {
            _allNodes.at(i)->_visited = false;
        }
        list<Node*> queue;
        // The OrgChart is empty
        if (_root == nullptr){
            return;
        }
        queue.push_back(_root);
        while (!queue.empty()){
            Node* curr = queue.front();
            queue.pop_front();
            for (size_t i = 0; i < curr->_children.size() ; ++i) {
                queue.push_back(curr->_children.at(i));
            }
            if (queue.empty()){
                curr->_next = nullptr;
                curr->_visited =true;
                return;
            }
            curr->_next = queue.front();
            curr->_visited =true;
        }
    }

    void OrgChart::revBFS() {
        for (size_t i = 0; i < _allNodes.size() ; ++i) {
            _allNodes.at(i)->_visited = false;
        }
        list<Node*> queue;
        // The OrgChart is empty
        if (_root == nullptr){
            return;
        }
        _root->_next = nullptr;
        queue.push_back(_root);
        while (!queue.empty()){
            Node* curr = queue.front();
            queue.pop_front();
            int length = (int)curr->_children.size();
            for (int i = length - 1 ; i >= 0  ; --i) {
                queue.push_back(curr->_children.at((unsigned int)i));
            }
            if (queue.empty()){
                curr->_visited =true;
                _tail = curr;
                return;
            }
            Node* temp = queue.front();
            temp->_next = curr;
            curr->_visited =true;
        }
    }

    void OrgChart::DFS_Visit(Node* curr){
        _preOrder.push_back(curr);
        for (size_t i = 0; i < curr->_children.size(); ++i) {
            if (!(curr->_children.at(i)->_visited)){
                DFS_Visit(curr->_children.at(i));
            }
        }
        curr->_visited = true;
    }


    void OrgChart::DFS(){
        for (size_t i = 0; i < _allNodes.size() ; ++i) {
            _allNodes.at(i)->_visited = false;
        }
        for (size_t i = 0; i < _allNodes.size() ; ++i) {
            if (!(_allNodes.at(i)->_visited)){
                DFS_Visit(_allNodes.at(i));
            }
        }
    }

}

