/*
 * [변형 문제 4]
 * 생성된 이진 트리를 전위 순회(Preorder Traversal)하여 
 * 전위 표기식(Prefix Expression)으로 화면에 출력하는 함수 preorder를 작성하라.
 */
void preorder(treePointer ptr) {
    if (ptr) {
        // Root 방문
        if (ptr->data == AND) printf("&");
        else if (ptr->data == OR) printf("|");
        else if (ptr->data == NOT) printf("~");
        else printf("%c", ptr->var);
        
        // Left -> Right
        preorder(ptr->leftChild);
        preorder(ptr->rightChild);
    }
}