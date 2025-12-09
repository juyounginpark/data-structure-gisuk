/*
 * [변형 문제 1]
 * 위에서 구성한 명제식 이진 트리의 높이(Height)를 구하는 함수 GetHeight를 작성하라.
 * (Leaf 노드의 높이는 1로 가정한다.)
 */
int GetHeight(treePointer ptr) {
    if (ptr == NULL) return 0;
    
    int leftH = GetHeight(ptr->leftChild);
    int rightH = GetHeight(ptr->rightChild);
    
    // 왼쪽과 오른쪽 중 큰 높이에 1을 더함
    return (leftH > rightH ? leftH : rightH) + 1;
}