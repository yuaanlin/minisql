#include <stdio.h>
#include <string>
#include <vector>

#include "../Index/Index.h"
#include "../BPTree/BPTree.h"

BPTreeNode_int::BPTreeNode_int(int degree, bool LeafNode)
    : isleaf(LeafNode), degree(degree) {
    this->KeyNum = 0;
    this->NextLeafNode = NULL;
    for (int i = 0; i < degree; i++) {
        this->children.push_back(NULL);
        this->KeyArray.push_back(0);
        this->ValArray.push_back(0);
    }
}

bool BPTreeNode_int::searchkey_node(int key, int& index) {
    if (this->KeyNum == 0) {
        index = 0;
        return false;
    } else {
        if (key < this->KeyArray[0]) {
            index = 0;
            return false;
        } else if (key > this->KeyArray[this->KeyNum - 1]) {
            index = this->KeyNum;
            return false;
        } else {
            for (int i = 0; i < this->KeyNum; i++) {
                if (this->KeyArray[i] == key) {
                    index = i;
                    return true;
                } else if (key > this->KeyArray[i]) {
                    continue;
                } else {
                    index = i;
                    return false;
                }
            }
        }
    }
}

BPTreeNode_int* BPTreeNode_int::splite(int& key) {
    int MinNode = (this->degree - 1) / 2;
    BPTreeNode_int* NewNode = new BPTreeNode_int(this->degree, this->isleaf);
    if (NewNode = NULL) return NULL;  //提示出错：申请新节点失败
    if (this->isleaf) {               //叶节点
        key = this->KeyArray[MinNode + 1];
        for (int i = MinNode + 1; i < degree; i++) {
            NewNode->KeyArray[i - MinNode - 1] = this->KeyArray[i];
            NewNode->ValArray[i - MinNode - 1] = this->ValArray[i];
            this->KeyArray[i] = this->ValArray[i] = 0;
        }
        NewNode->NextLeafNode = this->NextLeafNode;
        this->NextLeafNode = NewNode;
        NewNode->KeyNum = MinNode;
        this->KeyNum = MinNode + 1;
    } else {  //非叶
        key = this->KeyArray[MinNode];
        for (int i = MinNode + 1; i <= degree; i++) {
            NewNode->children[i - MinNode - 1] = this->children[i];
            this->children[i] = NULL;
        }
        for (int i = MinNode + 1; i < degree; i++) {
            NewNode->KeyArray[i - MinNode - 1] = this->KeyArray[i];
            this->KeyArray[i] = 0;
        }
        this->KeyArray[MinNode] = 0;
        NewNode->KeyNum = MinNode;
        this->KeyNum = MinNode;
    }
    NewNode->parent = this->parent;
    return NewNode;
}

int BPTreeNode_int::AddToBranch(int& key) {
    if (this->KeyNum == 0) {
        this->KeyArray[0] = key;
        this->KeyNum++;
        return 0;
    } else {
        int index = 0;
        if (this->searchkey_node(key, index))
            return -1;  //提示出错：此键已存在
        else {
            for (int i = this->KeyNum; i > index; i--) {
                this->KeyArray[i] = this->KeyArray[i - 1];
                this->children[i + 1] = this->children[i];
            }
            this->KeyArray[index] = key;
            this->children[index + 1] = NULL;
            this->KeyNum++;
            return index;
        }
    }
}

int BPTreeNode_int::AddToLeaf(int& key, int val) {
    if (!isleaf)
        return -1;  //提示出错：非叶
    else if (this->KeyNum == 0) {
        this->KeyNum++;
        this->KeyArray[0] = key;
        this->ValArray[0] = val;
        return 0;
    } else {
        int index = 0;
        if (this->searchkey_node(key, index))
            return -1;  //提示出错：此键已存在
        else {
            for (int i = this->KeyNum; i > index; i--) {
                this->KeyArray[i] = this->KeyArray[i - 1];
                this->ValArray[i] = this->ValArray[i - 1];
            }
            this->KeyArray[index] = key;
            this->ValArray[index] = val;
            this->KeyNum++;
            return index;
        }
    }
}

bool BPTreeNode_int::deletekey(int index) {
    if (index > this->KeyNum)
        return false;  //提示出错：不在此节点
    else {
        if (this->isleaf) {  //叶
            for (int i = index; i < this->KeyNum - 1; i++) {
                this->KeyArray[i] = this->KeyArray[i + 1];
                this->ValArray[i] = this->ValArray[i + 1];
            }
            this->KeyArray[this->KeyNum - 1] =
                this->ValArray[this->KeyNum - 1] = 0;
        } else {  //非叶
            for (int i = index; i < this->KeyNum - 1; i++) {
                this->KeyArray[i] = this->KeyArray[i + 1];
                this->children[i + 1] = this->children[i + 2];
            }
            this->KeyArray[this->KeyNum - 1] = 0;
            this->children[this->KeyNum] = NULL;
        }
        this->KeyNum--;
        return true;
    }
}

void BPTree_int::InitTree() {
    this->pRoot = new BPTreeNode_int(degree, true);
    this->pLeftLeaf = pRoot;
    this->NodeNum = 1;
    this->height = 0;
}

BPTree_int::BPTree_int(string name, int KeySize, int degree)
    : FileName(name), KeySize(KeySize), degree(degree) {
    InitTree();
}

BPTree_int::~BPTree_int() {
    this->DropTree(this->pRoot);
    this->KeyNum = 0;
    this->pRoot = NULL;
    this->height = 0;
}

void BPTree_int::DropTree(BPTreeNode_int* node) {
    if (!node) return;
    if (node->isleaf != 0) {
        for (int i = 0; i < node->KeyNum; i++) {
            DropTree(node->children[i]);
            node->children[i] = NULL;
        }
    }
    delete node;
    this->NodeNum--;
    return;
}

BPTreeNode_int* BPTree_int::searchkey_tree(
    int key, BPTreeNode_int* node) {  //在以node为根的树中找key
    int index = 0;
    int canfind = node->searchkey_node(key, index);
    if (canfind) {
        if (node->isleaf)
            return node;
        else {
            node = node->children[index + 1];
            while (!node->isleaf) node = node->children[0];
            return node;
        }
    } else {
        if (node->isleaf)
            return node;
        else
            return searchkey_tree(key, node->children[index]);
    }
}

BPTreeNode_int* BPTree_int::findmin(BPTreeNode_int* node) {
    if (node->isleaf)
        return node;
    else
        return node->children[0];
}

bool BPTree_int::InsertKey(int& key, int val) {
    int index = 0;
    BPTreeNode_int* TN = searchkey_tree(key, this->pRoot);  // TN=targetnode
    if (TN->searchkey_node(key, index))
        return 0;  //要插入的键已存在
    else {
        TN->AddToLeaf(key, val);
        if (TN->KeyNum >= degree) maintain(TN);
    }
    this->KeyNum++;
    return true;
}

bool BPTree_int::maintain(BPTreeNode_int* node) {
    int key;
    BPTreeNode_int* sib = node->splite(key);
    this->NodeNum++;
    if (node->isroot) {
        BPTreeNode_int* newroot = new BPTreeNode_int(degree);
        if (newroot == NULL)
            return false;  //提示出错：申请节点失败
        else {
            this->pRoot = newroot;
            this->height++;
            this->NodeNum++;
            node->parent = sib->parent = newroot;
            newroot->AddToBranch(key);
            newroot->children[0] = node;
            newroot->children[1] = sib;
            return true;
        }
    } else {
        sib->parent = node->parent;
        int index = node->parent->AddToBranch(key);
        node->parent->children[index + 1] = sib;
        if (node->parent->KeyNum >= degree) return maintain(node->parent);
        return true;
    }
}

bool BPTree_int::trim(BPTreeNode_int* node) {
    int MK = (degree - 1) / 2;
    if (((node->isleaf) && (node->KeyNum >= MK)) ||
        ((!node->isleaf) && (node->KeyNum >= MK - 1))) {
        return true;
    }                    //无需调整
    if (node->isroot) {  //根
        if (node->KeyNum)
            return true;
        else if (node->isleaf) {
            this->DropTree(this->pRoot);
        } else {
            this->pRoot = node->children[0];
            delete node;
            this->pRoot->parent = NULL;
            this->height--;
            this->NodeNum--;
        }
    }
    BPTreeNode_int* parent = node->parent;
    BPTreeNode_int* brother = NULL;
    if (node->isleaf) {  //叶
        int j = 0;
        while (parent->children[j] != node) j++;  // j为此node在parent中的位置
        if (((parent->children[0] != node) &&
             (parent->children[j - 1]->KeyNum > MK)) ||
            ((parent == node->NextLeafNode->parent) &&
             (node->NextLeafNode->KeyNum > MK))) {  //兄弟节点有富余
            if (parent->children[0] !=
                node) {  //有左兄弟,由上一行条件知此时左兄弟必有富余，直接借
                for (int i = node->KeyNum - 1; i >= 0; i--) {
                    node->KeyArray[i + 1] = node->KeyArray[i];
                    node->ValArray[i + 1] = node->ValArray[i];
                }
                node->KeyArray[0] = brother->KeyArray[brother->KeyNum - 1];
                node->ValArray[0] = brother->ValArray[brother->KeyNum - 1];
                brother->KeyArray[brother->KeyNum - 1] =
                    brother->ValArray[brother->KeyNum - 1] = 0;
                brother->KeyNum--;
                node->KeyNum++;
                parent->KeyArray[j] = node->KeyArray[0];
                return 1;
            } else {  //分析右兄弟
                brother = node->NextLeafNode;
                node->KeyArray[node->KeyNum] = brother->KeyArray[0];
                node->ValArray[node->KeyNum] = brother->ValArray[0];
                node->KeyNum++;
                brother->deletekey(0);
                if (node == parent->children[0])
                    parent->KeyArray[0] = brother->KeyArray[0];
                else
                    parent->KeyArray[j + 1] = brother->KeyArray[0];
                return 1;
            }
        } else {                                //做合并
            if (parent->children[0] != node) {  //跟左兄弟合并
                brother = parent->children[j - 1];
                parent->deletekey(j);
                for (int i = 0; i < node->KeyNum; i++) {
                    brother->KeyArray[i + brother->KeyNum] = node->KeyArray[i];
                    brother->ValArray[i + brother->KeyNum] = node->ValArray[i];
                }
                brother->KeyNum += node->KeyNum;
                brother->NextLeafNode = node->NextLeafNode;
                delete node;
                this->NodeNum--;
            } else {  //跟右兄弟合并
                brother = node->NextLeafNode;
                for (int i = 0; i < brother->KeyNum; i++) {
                    node->KeyArray[node->KeyNum + i] = brother->KeyArray[i];
                    node->ValArray[node->KeyNum + i] = brother->KeyArray[i];
                }
                if (node == parent->children[0])
                    parent->deletekey(0);
                else
                    parent->deletekey(j + 1);
                node->KeyNum += brother->KeyNum;
                node->NextLeafNode = brother->NextLeafNode;
                delete brother;
                this->NodeNum--;
            }
            return trim(parent);
        }

    } else {  //非叶非根
        int j = 0;
        while (parent->children[j] != node) j++;
        if (((parent->children[0] != node) &&
             (parent->children[j - 1]->KeyNum >= MK)) ||
            ((parent == node->NextLeafNode->parent) &&
             (node->NextLeafNode->KeyNum >= MK))) {  //兄弟节点有富余
            if (parent->children[0] != node) {       //分析左兄弟
                brother = parent->children[j - 1];
                for (int i = node->KeyNum - 1; i >= 0; i--) {
                    node->KeyArray[i + 1] = node->KeyArray[i];
                }
                for (int i = node->KeyNum; i >= 0; i--) {
                    node->children[i + 1] = node->children[i];
                }
                node->children[0] = brother->children[brother->KeyNum];
                node->KeyArray[0] = parent->KeyArray[j - 1];
                node->KeyNum++;
                parent->KeyArray[j - 1] =
                    brother->KeyArray[brother->KeyNum - 1];
                brother->children[brother->KeyNum]->parent = node;
                brother->deletekey(brother->KeyNum - 1);
            } else {  //分析右兄弟
                brother = parent->children[j + 1];
                if (brother->KeyNum >= MK) {  //右兄有富余
                    node->KeyArray[node->KeyNum] = brother->KeyArray[0];
                    node->children[node->KeyNum + 1] = brother->children[0];
                    node->KeyNum++;
                    if (node == parent->children[0])
                        parent->KeyArray[0] = brother->KeyArray[0];
                    else
                        parent->KeyArray[j] = brother->KeyArray[0];
                    brother->children[0] = brother->children[1];
                    brother->deletekey(0);
                    return 1;
                }
            }
        } else {                                //做合并
            if (parent->children[0] != node) {  //跟左兄弟合并
                brother = parent->children[j - 1];
                parent->deletekey(j);
                for (int i = 0; i < node->KeyNum; i++) {
                    brother->KeyArray[i + brother->KeyNum] = node->KeyArray[i];
                    brother->children[i + brother->KeyNum] = node->children[i];
                    brother->children[i + brother->KeyNum]->parent = brother;
                }
                brother->KeyNum += node->KeyNum;
                brother->children[brother->KeyNum + node->KeyNum] =
                    node->children[node->KeyNum];
                brother->children[brother->KeyNum + node->KeyNum]->parent =
                    brother;
                delete node;
                this->NodeNum--;
            } else {  //跟右兄弟合并
                brother = parent->children[j + 1];
                if (node == parent->children[0])
                    parent->deletekey(0);
                else
                    parent->deletekey(j + 1);
                for (int i = 0; i < brother->KeyNum; i++) {
                    node->KeyArray[i + node->KeyNum] = brother->KeyArray[i];
                    node->children[i + node->KeyNum] = brother->children[i];
                    node->children[i + node->KeyNum]->parent = node;
                }
                node->KeyNum += brother->KeyNum;
                node->children[brother->KeyNum + node->KeyNum] =
                    brother->children[brother->KeyNum];
                node->children[brother->KeyNum + node->KeyNum]->parent = node;
                delete brother;
                this->NodeNum--;
            }
            return trim(parent);
        }
    }
    return 0;
}

bool BPTree_int::DeleteKey(int& key) {
    if (!this->pRoot)
        return 0;  //提示出错：空树
    else {
        BPTreeNode_int* TN = searchkey_tree(key, this->pRoot);
        int index = 0;
        if (TN->searchkey_node(key, index) == 0)
            return 0;  //提示出错：未找到需要删除的键
        else {
            TN->deletekey(index);
            this->KeyNum--;
            return trim(TN);
        }
    }
}

BPTreeNode_float::BPTreeNode_float(int degree, bool LeafNode)
    : isleaf(LeafNode), degree(degree) {
    this->KeyNum = 0;
    this->NextLeafNode = NULL;
    for (int i = 0; i < degree; i++) {
        this->children.push_back(NULL);
        this->KeyArray.push_back(0);
        this->ValArray.push_back(0);
    }
}

bool BPTreeNode_float::searchkey_node(float key, int& index) {
    if (this->KeyNum == 0) {
        index = 0;
        return false;
    } else {
        if (key < this->KeyArray[0]) {
            index = 0;
            return false;
        } else if (key > this->KeyArray[this->KeyNum - 1]) {
            index = this->KeyNum;
            return false;
        } else {
            for (int i = 0; i < this->KeyNum; i++) {
                if (this->KeyArray[i] == key) {
                    index = i;
                    return true;
                } else if (key > this->KeyArray[i]) {
                    continue;
                } else {
                    index = i;
                    return false;
                }
            }
        }
    }
}

BPTreeNode_float* BPTreeNode_float::splite(float& key) {
    int MinNode = (this->degree - 1) / 2;
    BPTreeNode_float* NewNode =
        new BPTreeNode_float(this->degree, this->isleaf);
    if (NewNode = NULL) return NULL;  //提示出错：申请新节点失败
    if (this->isleaf) {               //叶节点
        key = this->KeyArray[MinNode + 1];
        for (int i = MinNode + 1; i < degree; i++) {
            NewNode->KeyArray[i - MinNode - 1] = this->KeyArray[i];
            NewNode->ValArray[i - MinNode - 1] = this->ValArray[i];
            this->KeyArray[i] = this->ValArray[i] = 0;
        }
        NewNode->NextLeafNode = this->NextLeafNode;
        this->NextLeafNode = NewNode;
        NewNode->KeyNum = MinNode;
        this->KeyNum = MinNode + 1;
    } else {  //非叶
        key = this->KeyArray[MinNode];
        for (int i = MinNode + 1; i <= degree; i++) {
            NewNode->children[i - MinNode - 1] = this->children[i];
            this->children[i] = NULL;
        }
        for (int i = MinNode + 1; i < degree; i++) {
            NewNode->KeyArray[i - MinNode - 1] = this->KeyArray[i];
            this->KeyArray[i] = 0;
        }
        this->KeyArray[MinNode] = 0;
        NewNode->KeyNum = MinNode;
        this->KeyNum = MinNode;
    }
    NewNode->parent = this->parent;
    return NewNode;
}

int BPTreeNode_float::AddToBranch(float& key) {
    if (this->KeyNum == 0) {
        this->KeyArray[0] = key;
        this->KeyNum++;
        return 0;
    } else {
        int index = 0;
        if (this->searchkey_node(key, index))
            return -1;  //提示出错：此键已存在
        else {
            for (int i = this->KeyNum; i > index; i--) {
                this->KeyArray[i] = this->KeyArray[i - 1];
                this->children[i + 1] = this->children[i];
            }
            this->KeyArray[index] = key;
            this->children[index + 1] = NULL;
            this->KeyNum++;
            return index;
        }
    }
}

int BPTreeNode_float::AddToLeaf(float& key, int val) {
    if (!isleaf)
        return -1;  //提示出错：非叶
    else if (this->KeyNum == 0) {
        this->KeyNum++;
        this->KeyArray[0] = key;
        this->ValArray[0] = val;
        return 0;
    } else {
        int index = 0;
        if (this->searchkey_node(key, index))
            return -1;  //提示出错：此键已存在
        else {
            for (int i = this->KeyNum; i > index; i--) {
                this->KeyArray[i] = this->KeyArray[i - 1];
                this->ValArray[i] = this->ValArray[i - 1];
            }
            this->KeyArray[index] = key;
            this->ValArray[index] = val;
            this->KeyNum++;
            return index;
        }
    }
}

bool BPTreeNode_float::deletekey(int index) {
    if (index > this->KeyNum)
        return false;  //提示出错：不在此节点
    else {
        if (this->isleaf) {  //叶
            for (int i = index; i < this->KeyNum - 1; i++) {
                this->KeyArray[i] = this->KeyArray[i + 1];
                this->ValArray[i] = this->ValArray[i + 1];
            }
            this->KeyArray[this->KeyNum - 1] =
                this->ValArray[this->KeyNum - 1] = 0;
        } else {  //非叶
            for (int i = index; i < this->KeyNum - 1; i++) {
                this->KeyArray[i] = this->KeyArray[i + 1];
                this->children[i + 1] = this->children[i + 2];
            }
            this->KeyArray[this->KeyNum - 1] = 0;
            this->children[this->KeyNum] = NULL;
        }
        this->KeyNum--;
        return true;
    }
}

void BPTree_float::InitTree() {
    this->pRoot = new BPTreeNode_float(degree, true);
    this->pLeftLeaf = pRoot;
    this->NodeNum = 1;
    this->height = 0;
}

BPTree_float::BPTree_float(string name, int KeySize, int degree)
    : FileName(name), KeySize(KeySize), degree(degree) {
    InitTree();
}

BPTree_float::~BPTree_float() {
    this->DropTree(this->pRoot);
    this->KeyNum = 0;
    this->pRoot = NULL;
    this->height = 0;
}

void BPTree_float::DropTree(BPTreeNode_float* node) {
    if (!node) return;
    if (node->isleaf != 0) {
        for (int i = 0; i < node->KeyNum; i++) {
            DropTree(node->children[i]);
            node->children[i] = NULL;
        }
    }
    delete node;
    this->NodeNum--;
    return;
}

BPTreeNode_float* BPTree_float::searchkey_tree(
    float key, BPTreeNode_float* node) {  //在以node为根的树中找key
    int index = 0;
    int canfind = node->searchkey_node(key, index);
    if (canfind) {
        if (node->isleaf)
            return node;
        else {
            node = node->children[index + 1];
            while (!node->isleaf) node = node->children[0];
            return node;
        }
    } else {
        if (node->isleaf)
            return node;
        else
            return searchkey_tree(key, node->children[index]);
    }
}

BPTreeNode_float* BPTree_float::findmin(BPTreeNode_float* node) {
    if (node->isleaf)
        return node;
    else
        return node->children[0];
}

bool BPTree_float::InsertKey(float& key, int val) {
    int index = 0;
    BPTreeNode_float* TN = searchkey_tree(key, this->pRoot);  // TN=targetnode
    if (TN->searchkey_node(key, index))
        return 0;  //要插入的键已存在
    else {
        TN->AddToLeaf(key, val);
        if (TN->KeyNum >= degree) maintain(TN);
    }
    this->KeyNum++;
    return true;
}

bool BPTree_float::maintain(BPTreeNode_float* node) {
    float key;
    BPTreeNode_float* sib = node->splite(key);
    this->NodeNum++;
    if (node->isroot) {
        BPTreeNode_float* newroot = new BPTreeNode_float(degree);
        if (newroot == NULL)
            return false;  //提示出错：申请节点失败
        else {
            this->pRoot = newroot;
            this->height++;
            this->NodeNum++;
            node->parent = sib->parent = newroot;
            newroot->AddToBranch(key);
            newroot->children[0] = node;
            newroot->children[1] = sib;
            return true;
        }
    } else {
        sib->parent = node->parent;
        int index = node->parent->AddToBranch(key);
        node->parent->children[index + 1] = sib;
        if (node->parent->KeyNum >= degree) return maintain(node->parent);
        return true;
    }
}

bool BPTree_float::trim(BPTreeNode_float* node) {
    int MK = (degree - 1) / 2;
    if (((node->isleaf) && (node->KeyNum >= MK)) ||
        ((!node->isleaf) && (node->KeyNum >= MK - 1))) {
        return true;
    }                    //无需调整
    if (node->isroot) {  //根
        if (node->KeyNum)
            return true;
        else if (node->isleaf) {
            this->DropTree(this->pRoot);
        } else {
            this->pRoot = node->children[0];
            delete node;
            this->pRoot->parent = NULL;
            this->height--;
            this->NodeNum--;
        }
    }
    BPTreeNode_float* parent = node->parent;
    BPTreeNode_float* brother = NULL;
    if (node->isleaf) {  //叶
        int j = 0;
        while (parent->children[j] != node) j++;  // j为此node在parent中的位置
        if (((parent->children[0] != node) &&
             (parent->children[j - 1]->KeyNum > MK)) ||
            ((parent == node->NextLeafNode->parent) &&
             (node->NextLeafNode->KeyNum > MK))) {  //兄弟节点有富余
            if (parent->children[0] !=
                node) {  //有左兄弟,由上一行条件知此时左兄弟必有富余，直接借
                for (int i = node->KeyNum - 1; i >= 0; i--) {
                    node->KeyArray[i + 1] = node->KeyArray[i];
                    node->ValArray[i + 1] = node->ValArray[i];
                }
                node->KeyArray[0] = brother->KeyArray[brother->KeyNum - 1];
                node->ValArray[0] = brother->ValArray[brother->KeyNum - 1];
                brother->KeyArray[brother->KeyNum - 1] =
                    brother->ValArray[brother->KeyNum - 1] = 0;
                brother->KeyNum--;
                node->KeyNum++;
                parent->KeyArray[j] = node->KeyArray[0];
                return 1;
            } else {  //分析右兄弟
                brother = node->NextLeafNode;
                node->KeyArray[node->KeyNum] = brother->KeyArray[0];
                node->ValArray[node->KeyNum] = brother->ValArray[0];
                node->KeyNum++;
                brother->deletekey(0);
                if (node == parent->children[0])
                    parent->KeyArray[0] = brother->KeyArray[0];
                else
                    parent->KeyArray[j + 1] = brother->KeyArray[0];
                return 1;
            }
        } else {                                //做合并
            if (parent->children[0] != node) {  //跟左兄弟合并
                brother = parent->children[j - 1];
                parent->deletekey(j);
                for (int i = 0; i < node->KeyNum; i++) {
                    brother->KeyArray[i + brother->KeyNum] = node->KeyArray[i];
                    brother->ValArray[i + brother->KeyNum] = node->ValArray[i];
                }
                brother->KeyNum += node->KeyNum;
                brother->NextLeafNode = node->NextLeafNode;
                delete node;
                this->NodeNum--;
            } else {  //跟右兄弟合并
                brother = node->NextLeafNode;
                for (int i = 0; i < brother->KeyNum; i++) {
                    node->KeyArray[node->KeyNum + i] = brother->KeyArray[i];
                    node->ValArray[node->KeyNum + i] = brother->KeyArray[i];
                }
                if (node == parent->children[0])
                    parent->deletekey(0);
                else
                    parent->deletekey(j + 1);
                node->KeyNum += brother->KeyNum;
                node->NextLeafNode = brother->NextLeafNode;
                delete brother;
                this->NodeNum--;
            }
            return trim(parent);
        }

    } else {  //非叶非根
        int j = 0;
        while (parent->children[j] != node) j++;
        if (((parent->children[0] != node) &&
             (parent->children[j - 1]->KeyNum >= MK)) ||
            ((parent == node->NextLeafNode->parent) &&
             (node->NextLeafNode->KeyNum >= MK))) {  //兄弟节点有富余
            if (parent->children[0] != node) {       //分析左兄弟
                brother = parent->children[j - 1];
                for (int i = node->KeyNum - 1; i >= 0; i--) {
                    node->KeyArray[i + 1] = node->KeyArray[i];
                }
                for (int i = node->KeyNum; i >= 0; i--) {
                    node->children[i + 1] = node->children[i];
                }
                node->children[0] = brother->children[brother->KeyNum];
                node->KeyArray[0] = parent->KeyArray[j - 1];
                node->KeyNum++;
                parent->KeyArray[j - 1] =
                    brother->KeyArray[brother->KeyNum - 1];
                brother->children[brother->KeyNum]->parent = node;
                brother->deletekey(brother->KeyNum - 1);
            } else {  //分析右兄弟
                brother = parent->children[j + 1];
                int j = 0;
                while (parent->children[j] != node) j++;
                brother = node->NextLeafNode;
                if (brother->KeyNum >= MK) {  //右兄有富余
                    node->KeyArray[node->KeyNum] = brother->KeyArray[0];
                    node->children[node->KeyNum + 1] = brother->children[0];
                    node->KeyNum++;
                    if (node == parent->children[0])
                        parent->KeyArray[0] = brother->KeyArray[0];
                    else
                        parent->KeyArray[j] = brother->KeyArray[0];
                    brother->children[0] = brother->children[1];
                    brother->deletekey(0);
                    return 1;
                }
            }
        } else {                                //做合并
            if (parent->children[0] != node) {  //跟左兄弟合并
                brother = parent->children[j - 1];
                parent->deletekey(j);
                for (int i = 0; i < node->KeyNum; i++) {
                    brother->KeyArray[i + brother->KeyNum] = node->KeyArray[i];
                    brother->children[i + brother->KeyNum] = node->children[i];
                    brother->children[i + brother->KeyNum]->parent = brother;
                }
                brother->KeyNum += node->KeyNum;
                brother->children[brother->KeyNum + node->KeyNum] =
                    node->children[node->KeyNum];
                brother->children[brother->KeyNum + node->KeyNum]->parent =
                    brother;
                delete node;
                this->NodeNum--;
            } else {  //跟右兄弟合并
                brother = parent->children[j + 1];
                if (node == parent->children[0])
                    parent->deletekey(0);
                else
                    parent->deletekey(j + 1);
                for (int i = 0; i < brother->KeyNum; i++) {
                    node->KeyArray[i + node->KeyNum] = brother->KeyArray[i];
                    node->children[i + node->KeyNum] = brother->children[i];
                    node->children[i + node->KeyNum]->parent = node;
                }
                node->KeyNum += brother->KeyNum;
                node->children[brother->KeyNum + node->KeyNum] =
                    brother->children[brother->KeyNum];
                node->children[brother->KeyNum + node->KeyNum]->parent = node;
                delete brother;
                this->NodeNum--;
            }
            return trim(parent);
        }
    }
    return 0;
}

bool BPTree_float::DeleteKey(float& key) {
    if (!this->pRoot)
        return 0;  //提示出错：空树
    else {
        BPTreeNode_float* TN = searchkey_tree(key, this->pRoot);
        int index = 0;
        if (TN->searchkey_node(key, index) == 0)
            return 0;  //提示出错：未找到需要删除的键
        else {
            TN->deletekey(index);
            this->KeyNum--;
            return trim(TN);
        }
    }
}

BPTreeNode_string::BPTreeNode_string(int degree, bool LeafNode)
    : isleaf(LeafNode), degree(degree) {
    this->KeyNum = 0;
    this->NextLeafNode = NULL;
    for (int i = 0; i < degree; i++) {
        this->children.push_back(NULL);
        this->KeyArray.push_back(string());
        this->ValArray.push_back(0);
    }
}

bool BPTreeNode_string::searchkey_node(string key, int& index) {
    if (this->KeyNum == 0) {
        index = 0;
        return false;
    } else {
        if (key < this->KeyArray[0]) {
            index = 0;
            return false;
        } else if (key > this->KeyArray[this->KeyNum - 1]) {
            index = this->KeyNum;
            return false;
        } else {
            for (int i = 0; i < this->KeyNum; i++) {
                if (this->KeyArray[i] == key) {
                    index = i;
                    return true;
                } else if (key > this->KeyArray[i]) {
                    continue;
                } else {
                    index = i;
                    return false;
                }
            }
        }
    }
}

BPTreeNode_string* BPTreeNode_string::splite(string& key) {
    int MinNode = (this->degree - 1) / 2;
    BPTreeNode_string* NewNode =
        new BPTreeNode_string(this->degree, this->isleaf);
    if (NewNode = NULL) return NULL;  //提示出错：申请新节点失败
    if (this->isleaf) {               //叶节点
        key = this->KeyArray[MinNode + 1];
        for (int i = MinNode + 1; i < degree; i++) {
            NewNode->KeyArray[i - MinNode - 1] = this->KeyArray[i];
            NewNode->ValArray[i - MinNode - 1] = this->ValArray[i];
            this->KeyArray[i] = string();
            this->ValArray[i] = 0;
        }
        NewNode->NextLeafNode = this->NextLeafNode;
        this->NextLeafNode = NewNode;
        NewNode->KeyNum = MinNode;
        this->KeyNum = MinNode + 1;
    } else {  //非叶
        key = this->KeyArray[MinNode];
        for (int i = MinNode + 1; i <= degree; i++) {
            NewNode->children[i - MinNode - 1] = this->children[i];
            this->children[i] = NULL;
        }
        for (int i = MinNode + 1; i < degree; i++) {
            NewNode->KeyArray[i - MinNode - 1] = this->KeyArray[i];
            this->KeyArray[i] = string();
        }
        this->KeyArray[MinNode] = string();
        NewNode->KeyNum = MinNode;
        this->KeyNum = MinNode;
    }
    NewNode->parent = this->parent;
    return NewNode;
}

int BPTreeNode_string::AddToBranch(string& key) {
    if (this->KeyNum == 0) {
        this->KeyArray[0] = key;
        this->KeyNum++;
        return 0;
    } else {
        int index = 0;
        if (this->searchkey_node(key, index))
            return -1;  //提示出错：此键已存在
        else {
            for (int i = this->KeyNum; i > index; i--) {
                this->KeyArray[i] = this->KeyArray[i - 1];
                this->children[i + 1] = this->children[i];
            }
            this->KeyArray[index] = key;
            this->children[index + 1] = NULL;
            this->KeyNum++;
            return index;
        }
    }
}

int BPTreeNode_string::AddToLeaf(string& key, int val) {
    if (!isleaf)
        return -1;  //提示出错：非叶
    else if (this->KeyNum == 0) {
        this->KeyNum++;
        this->KeyArray[0] = key;
        this->ValArray[0] = val;
        return 0;
    } else {
        int index = 0;
        if (this->searchkey_node(key, index))
            return -1;  //提示出错：此键已存在
        else {
            for (int i = this->KeyNum; i > index; i--) {
                this->KeyArray[i] = this->KeyArray[i - 1];
                this->ValArray[i] = this->ValArray[i - 1];
            }
            this->KeyArray[index] = key;
            this->ValArray[index] = val;
            this->KeyNum++;
            return index;
        }
    }
}

bool BPTreeNode_string::deletekey(int index) {
    if (index > this->KeyNum)
        return false;  //提示出错：不在此节点
    else {
        if (this->isleaf) {  //叶
            for (int i = index; i < this->KeyNum - 1; i++) {
                this->KeyArray[i] = this->KeyArray[i + 1];
                this->ValArray[i] = this->ValArray[i + 1];
            }
            this->KeyArray[this->KeyNum - 1] =
                this->ValArray[this->KeyNum - 1] = 0;
        } else {  //非叶
            for (int i = index; i < this->KeyNum - 1; i++) {
                this->KeyArray[i] = this->KeyArray[i + 1];
                this->children[i + 1] = this->children[i + 2];
            }
            this->KeyArray[this->KeyNum - 1] = string();
            this->children[this->KeyNum] = NULL;
        }
        this->KeyNum--;
        return true;
    }
}

void BPTree_string::InitTree() {
    this->pRoot = new BPTreeNode_string(degree, true);
    this->NodeNum = 1;
    this->height = 0;
}

BPTree_string::BPTree_string(string name, int KeySize, int degree)
    : FileName(name), KeySize(KeySize), degree(degree) {
    InitTree();
}

BPTree_string::~BPTree_string() {
    this->DropTree(this->pRoot);
    this->KeyNum = 0;
    this->pRoot = NULL;
    this->height = 0;
}

void BPTree_string::DropTree(BPTreeNode_string* node) {
    if (!node) return;
    if (node->isleaf != 0) {
        for (int i = 0; i < node->KeyNum; i++) {
            DropTree(node->children[i]);
            node->children[i] = NULL;
        }
    }
    delete node;
    this->NodeNum--;
    return;
}

BPTreeNode_string* BPTree_string::searchkey_tree(
    string key, BPTreeNode_string* node) {  //在以node为根的树中找key
    int index = 0;
    int canfind = node->searchkey_node(key, index);
    if (canfind) {
        if (node->isleaf)
            return node;
        else {
            node = node->children[index + 1];
            while (!node->isleaf) node = node->children[0];
            return node;
        }
    } else {
        if (node->isleaf)
            return node;
        else
            return searchkey_tree(key, node->children[index]);
    }
}

BPTreeNode_string* BPTree_string::findmin(BPTreeNode_string* node) {
    if (node->isleaf)
        return node;
    else
        return node->children[0];
}

bool BPTree_string::InsertKey(string& key, int val) {
    int index = 0;
    BPTreeNode_string* TN = searchkey_tree(key, this->pRoot);  // TN=targetnode
    if (TN->searchkey_node(key, index))
        return 0;  //要插入的键已存在
    else {
        TN->AddToLeaf(key, val);
        if (TN->KeyNum >= degree) maintain(TN);
    }
    this->KeyNum++;
    return true;
}

bool BPTree_string::maintain(BPTreeNode_string* node) {
    string key;
    BPTreeNode_string* sib = node->splite(key);
    this->NodeNum++;
    if (node->isroot) {
        BPTreeNode_string* newroot = new BPTreeNode_string(degree);
        if (newroot == NULL)
            return false;  //提示出错：申请节点失败
        else {
            this->pRoot = newroot;
            this->height++;
            this->NodeNum++;
            node->parent = sib->parent = newroot;
            newroot->AddToBranch(key);
            newroot->children[0] = node;
            newroot->children[1] = sib;
            return true;
        }
    } else {
        sib->parent = node->parent;
        int index = node->parent->AddToBranch(key);
        node->parent->children[index + 1] = sib;
        if (node->parent->KeyNum >= degree) return maintain(node->parent);
        return true;
    }
}

bool BPTree_string::trim(BPTreeNode_string* node) {
    int MK = (degree - 1) / 2;
    if (((node->isleaf) && (node->KeyNum >= MK)) ||
        ((!node->isleaf) && (node->KeyNum >= MK - 1))) {
        return true;
    }                    //无需调整
    if (node->isroot) {  //根
        if (node->KeyNum)
            return true;
        else if (node->isleaf) {
            this->DropTree(this->pRoot);
        } else {
            this->pRoot = node->children[0];
            delete node;
            this->pRoot->parent = NULL;
            this->height--;
            this->NodeNum--;
        }
    }
    BPTreeNode_string* parent = node->parent;
    BPTreeNode_string* brother = NULL;
    if (node->isleaf) {  //叶
        int j = 0;
        while (parent->children[j] != node) j++;  // j为此node在parent中的位置
        if (((parent->children[0] != node) &&
             (parent->children[j - 1]->KeyNum > MK)) ||
            ((parent == node->NextLeafNode->parent) &&
             (node->NextLeafNode->KeyNum > MK))) {  //兄弟节点有富余
            if (parent->children[0] !=
                node) {  //有左兄弟,由上一行条件知此时左兄弟必有富余，直接借
                for (int i = node->KeyNum - 1; i >= 0; i--) {
                    node->KeyArray[i + 1] = node->KeyArray[i];
                    node->ValArray[i + 1] = node->ValArray[i];
                }
                node->KeyArray[0] = brother->KeyArray[brother->KeyNum - 1];
                node->ValArray[0] = brother->ValArray[brother->KeyNum - 1];
                brother->KeyArray[brother->KeyNum - 1] =
                    brother->ValArray[brother->KeyNum - 1] = 0;
                brother->KeyNum--;
                node->KeyNum++;
                parent->KeyArray[j] = node->KeyArray[0];
                return 1;
            } else {  //分析右兄弟
                brother = node->NextLeafNode;
                node->KeyArray[node->KeyNum] = brother->KeyArray[0];
                node->ValArray[node->KeyNum] = brother->ValArray[0];
                node->KeyNum++;
                brother->deletekey(0);
                if (node == parent->children[0])
                    parent->KeyArray[0] = brother->KeyArray[0];
                else
                    parent->KeyArray[j + 1] = brother->KeyArray[0];
                return 1;
            }
        } else {                                //做合并
            if (parent->children[0] != node) {  //跟左兄弟合并
                brother = parent->children[j - 1];
                parent->deletekey(j);
                for (int i = 0; i < node->KeyNum; i++) {
                    brother->KeyArray[i + brother->KeyNum] = node->KeyArray[i];
                    brother->ValArray[i + brother->KeyNum] = node->ValArray[i];
                }
                brother->KeyNum += node->KeyNum;
                brother->NextLeafNode = node->NextLeafNode;
                delete node;
                this->NodeNum--;
            } else {  //跟右兄弟合并
                brother = node->NextLeafNode;
                for (int i = 0; i < brother->KeyNum; i++) {
                    node->KeyArray[node->KeyNum + i] = brother->KeyArray[i];
                    node->ValArray[node->KeyNum + i] = brother->ValArray[i];
                }
                if (node == parent->children[0])
                    parent->deletekey(0);
                else
                    parent->deletekey(j + 1);
                node->KeyNum += brother->KeyNum;
                node->NextLeafNode = brother->NextLeafNode;
                delete brother;
                this->NodeNum--;
            }
            return trim(parent);
        }

    } else {  //非叶非根
        int j = 0;
        while (parent->children[j] != node) j++;
        if (((parent->children[0] != node) &&
             (parent->children[j - 1]->KeyNum >= MK)) ||
            ((parent == node->NextLeafNode->parent) &&
             (node->NextLeafNode->KeyNum >= MK))) {  //兄弟节点有富余
            if (parent->children[0] != node) {       //分析左兄弟
                brother = parent->children[j - 1];
                for (int i = node->KeyNum - 1; i >= 0; i--) {
                    node->KeyArray[i + 1] = node->KeyArray[i];
                }
                for (int i = node->KeyNum; i >= 0; i--) {
                    node->children[i + 1] = node->children[i];
                }
                node->children[0] = brother->children[brother->KeyNum];
                node->KeyArray[0] = parent->KeyArray[j - 1];
                node->KeyNum++;
                parent->KeyArray[j - 1] =
                    brother->KeyArray[brother->KeyNum - 1];
                brother->children[brother->KeyNum]->parent = node;
                brother->deletekey(brother->KeyNum - 1);
            } else {  //分析右兄弟
                brother = parent->children[j + 1];
                int j = 0;
                while (parent->children[j] != node) j++;
                brother = node->NextLeafNode;
                if (brother->KeyNum >= MK) {  //右兄有富余
                    node->KeyArray[node->KeyNum] = brother->KeyArray[0];
                    node->children[node->KeyNum + 1] = brother->children[0];
                    node->KeyNum++;
                    if (node == parent->children[0])
                        parent->KeyArray[0] = brother->KeyArray[0];
                    else
                        parent->KeyArray[j] = brother->KeyArray[0];
                    brother->children[0] = brother->children[1];
                    brother->deletekey(0);
                    return 1;
                }
            }
        } else {                                //做合并
            if (parent->children[0] != node) {  //跟左兄弟合并
                brother = parent->children[j - 1];
                parent->deletekey(j);
                for (int i = 0; i < node->KeyNum; i++) {
                    brother->KeyArray[i + brother->KeyNum] = node->KeyArray[i];
                    brother->children[i + brother->KeyNum] = node->children[i];
                    brother->children[i + brother->KeyNum]->parent = brother;
                }
                brother->KeyNum += node->KeyNum;
                brother->children[brother->KeyNum + node->KeyNum] =
                    node->children[node->KeyNum];
                brother->children[brother->KeyNum + node->KeyNum]->parent =
                    brother;
                delete node;
                this->NodeNum--;
            } else {  //跟右兄弟合并
                brother = parent->children[j + 1];
                if (node == parent->children[0])
                    parent->deletekey(0);
                else
                    parent->deletekey(j + 1);
                for (int i = 0; i < brother->KeyNum; i++) {
                    node->KeyArray[i + node->KeyNum] = brother->KeyArray[i];
                    node->children[i + node->KeyNum] = brother->children[i];
                    node->children[i + node->KeyNum]->parent = node;
                }
                node->KeyNum += brother->KeyNum;
                node->children[brother->KeyNum + node->KeyNum] =
                    brother->children[brother->KeyNum];
                node->children[brother->KeyNum + node->KeyNum]->parent = node;
                delete brother;
                this->NodeNum--;
            }
            return trim(parent);
        }
    }
    return 0;
}

bool BPTree_string::DeleteKey(string& key) {
    if (!this->pRoot)
        return 0;  //提示出错：空树
    else {
        BPTreeNode_string* TN = searchkey_tree(key, this->pRoot);
        int index = 0;
        if (TN->searchkey_node(key, index) == 0)
            return 0;  //提示出错：未找到需要删除的键
        else {
            TN->deletekey(index);
            this->KeyNum--;
            return trim(TN);
        }
    }
}
