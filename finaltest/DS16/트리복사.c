/*
 * [변형 문제 5]
 * 주어진 명제식 이진 트리를 복사하여 새로운 트리를 생성하고 
 * 그 루트 포인터를 반환하는 copyTree 함수를 작성하라.
 */
treePointer copyTree(treePointer original) {
    if (!original) return NULL;
    
    treePointer temp = (treePointer)malloc(sizeof(tNode));
    temp->var = original->var;
    temp->data = original->data;
    temp->value = original->value;
    
    temp->leftChild = copyTree(original->leftChild);
    temp->rightChild = copyTree(original->rightChild);
    
    return temp;
}