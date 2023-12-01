//Helping functions
int balanced (Node* _root)
{
    return getHeightRec(_root->pLeft) - getHeightRec(_root->pRight);
}

Node* rotation(Node* _root)
{
    if (balanced(_root) == 2)
    {
        if (balanced(_root->pLeft) >= 0)
            _root = rotateRight(_root);
        else
        {
            _root->pLeft = rotateLeft(_root->pLeft);
            _root = rotateRight(_root);
        }
    }
    else if (balanced(_root) == -2)
    {
        if (balanced(_root->pRight) <= 0)
            _root = rotateLeft(_root);
        else
        {
            _root->pRight = rotateRight(_root->pRight);
            _root = rotateLeft(_root);
        }
    }
    return _root;
}

Node* getMaxLeft(Node* _root)
{
    Node* curr = _root;
    while(curr && curr->pRight!=nullptr)
    {
        curr = curr->pRight;
    }
    return curr;
}

Node* recDit(Node* _root, T value)
{
    if (!_root)
        return nullptr;
    if (value < _root->data)
    {
        _root->pLeft = recDit(_root->pLeft,value);
        while (true)
        {
            if (balanced(_root) ==1)
            {
                _root->balance =LH;
                break;
            }
            if (balanced(_root) ==0)
            {
                _root->balance = EH;
                break;
            }
            if (balanced(_root) ==-1)
            {
                _root->balance = RH;
                break;
            }
            _root = rotation(_root);
        }
    }
    else if (value > _root->data)
    {
        _root->pRight = recDit(_root->pRight,value);
        while (true)
        {
            if (balanced(_root) ==1)
            {
                _root->balance =LH;
                break;
            }
            if (balanced(_root) ==0)
            {
                _root->balance = EH;
                break;
            }
            if (balanced(_root) ==-1)
            {
                _root->balance = RH;
                break;
            }
            _root = rotation(_root);
        }
    }
    else 
    {
        if (_root->pLeft==nullptr && _root->pRight ==nullptr)
            return nullptr;
        else if (_root->pLeft ==nullptr)
        {
            Node* tmp = _root->pRight;
            delete _root;
            return tmp;
        }
        else if (_root->pRight == nullptr)
        {
            Node* tmp = _root->pLeft;
            delete _root;
            return tmp;
        }
        Node* dlt = getMaxLeft(_root->pLeft);
        _root->data = dlt->data;
        _root->pLeft = recDit(_root->pLeft,dlt->data);
        
    }
    return _root;
}


void remove(const T &value){
    root= recDit(root, value);
    //TODO
    
}
