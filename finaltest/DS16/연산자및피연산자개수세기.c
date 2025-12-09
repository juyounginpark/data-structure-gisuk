/*
 * [변형 문제 2]
 * 구성된 이진 트리에서 피연산자(a, b, c 등)의 개수와 
 * 연산자(&, |, ~)의 개수를 각각 세어 출력하는 함수 CountNodes를 작성하라.
 */
void CountNodes(treePointer ptr, int* op_count, int* var_count) {
    if (ptr) {
        if (ptr->data == AND || ptr->data == OR || ptr->data == NOT) {
            (*op_count)++;
        } else {
            (*var_count)++;
        }
        CountNodes(ptr->leftChild, op_count, var_count);
        CountNodes(ptr->rightChild, op_count, var_count);
    }
}
// 호출 예:
// int ops = 0, vars = 0;
// CountNodes(root, &ops, &vars);
// printf("Operators: %d, Operands: %d\n", ops, vars);