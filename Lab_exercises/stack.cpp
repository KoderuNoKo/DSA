// cau 1
int baseballScore(string ops)
{
    int temp1 = 0;
    int temp2 = 0;
	stack<int> stk;
	for (char op : ops) {
		switch (op)
		{
		case 'C': 
			stk.pop();
			break;

		case 'D':
			stk.push(stk.top() * 2);
			break;

		case '+':
			temp1 = stk.top();
			stk.pop();
			temp2 = stk.top();
			stk.push(temp1);
			stk.push(temp1 + temp2);
			break;

		default:
			stk.push(op - '0');
			break;
		}
	}

	int sum = 0;
	while (!stk.empty()) {
		sum += stk.top();
		stk.pop();
	}
	return sum;
}

// cau 2
void push(T item) {
    // TODO: Push new element into the top of the stack
    list.add(item);
}

T pop() {
    // TODO: Remove an element on top of the stack
    T temp = list.get(list.size() - 1);
    list.removeAt(list.size() - 1);
    return temp;
}

T top() {
    // TODO: Get value of the element on top of the stack
      return list.get(list.size() - 1);
}

bool empty() {
    // TODO: Determine if the stack is empty
    return list.empty();
}

int size() {
    // TODO: Get the size of the stack
    return list.size();
}

void clear() {
    // TODO: Clear all elements of the stack
    list.clear();
}

// cau 3
// iostream, stack and vector are included

std::vector<int> nextGreater(std::vector<int>& arr) {
    int N = arr.size();
    std::vector<int> result(N, -1);
    std::stack<int> st;

    for (int i = 0; i < N; ++i) { // Exclude the last element
        while (!st.empty() && arr[i] > arr[st.top()]) {
            result[st.top()] = arr[i];
            st.pop();
        }
        st.push(i);
    }

    return result;
}

// cau 4
int evaluatePostfix(std::string expr) {
    std::stack<int> operands;

    for (size_t i = 0; i < expr.size(); i++) {
        char c = expr[i];
        if (c == ' ') {
            // Skip whitespace
            continue;
        } else if (isdigit(c)) {
            // Handle multi-digit operands
            int operand = 0;
            while (isdigit(c)) {
                operand = operand * 10 + (c - '0');
                c = expr[++i];
            }
            operands.push(operand);
        } else {
            // If the character is an operator, pop the top two operands from the stack
            if (operands.size() < 2) {
                std::cerr << "Invalid expression." << std::endl;
                return -1; // Error code
            }
            int operand2 = operands.top();
            operands.pop();
            int operand1 = operands.top();
            operands.pop();

            // Perform the operation and push the result back onto the stack
            switch (c) {
                case '+':
                    operands.push(operand1 + operand2);
                    break;
                case '-':
                    operands.push(operand1 - operand2);
                    break;
                case '*':
                    operands.push(operand1 * operand2);
                    break;
                case '/':
                    operands.push(operand1 / operand2);
                    break;
                default:
                    std::cerr << "Invalid operator: " << c << std::endl;
                    return -1; // Error code
            }
        }
    }

    // The result should be the only element left in the stack
    if (!operands.empty()) {
        return operands.top();
    } else {
        std::cerr << "Invalid expression." << std::endl;
        return -1; // Error code
    }
}

// cau 5
const int N = 5; // Size of the maze

bool isValid(int x, int y) {
    // Check if the given coordinates are within the bounds of the maze
    return (x >= 0 && x < N && y >= 0 && y < N);
}

bool dfs(int maze[N][N], int x, int y, int fx, int fy, bool visited[N][N]) {
    // If the current position is the food's position, return true
    if (x == fx && y == fy) {
        return true;
    }

    // Mark the current position as visited
    visited[x][y] = true;

    // Define possible moves (up, left, down, right)
    int dx[] = {-1, 0, 1, 0};
    int dy[] = {0, -1, 0, 1};

    // Try all possible moves
    for (int i = 0; i < 4; i++) {
        int newX = x + dx[i];
        int newY = y + dy[i];

        // Check if the new position is valid and not visited
        if (isValid(newX, newY) && maze[newX][newY] == 1 && !visited[newX][newY]) {
            // Recursively explore the new position
            if (dfs(maze, newX, newY, fx, fy, visited)) {
                return true; // If a path is found, return true
            }
        }
    }

    // If no path is found from this position, backtrack and return false
    return false;
}

bool canEatFood(int maze[N][N], int fx, int fy) {
    // Create a visited array to keep track of visited positions
    bool visited[N][N];
    memset(visited, false, sizeof(visited));

    // Start DFS from the rat's initial position (0, 0)
    return dfs(maze, 0, 0, fx, fy, visited);
}

// cau 6
std::string removeDuplicates(std::string S) {
    std::stack<char> charStack;

    for (char c : S) {
        // If the stack is not empty and the top of the stack is equal to the current character,
        // remove the top element (remove duplicates)
        if (!charStack.empty() && charStack.top() == c) {
            charStack.pop();
        } else {
            charStack.push(c);
        }
    }

    // Reconstruct the result string from the stack
    std::string result;
    while (!charStack.empty()) {
        result = charStack.top() + result;
        charStack.pop();
    }

    return result;
}

// cau 7
vector<int> stock_span(const vector<int>& ns) {
    int n = ns.size();
    std::vector<int> spans(n, 0);  // Initialize an array to store the spans
    std::stack<int> stack;  // Create an empty stack to store indices

    for (int i = 0; i < n; i++) {
        // Pop elements from the stack while they are smaller than or equal to prices[i]
        while (!stack.empty() && ns[i] >= ns[stack.top()]) {
            stack.pop();
        }

        // The span for the current day is the difference between the current day's index
        // and the index of the previous greater element (or -1 if none)
        spans[i] = stack.empty() ? i + 1 : i - stack.top();

        // Push the current index onto the stack
        stack.push(i);
    }

    return spans;
}

// cau 8
bool isValidParentheses(string s) {
    stack<char> stk;

    for (char c : s) {
        if (c == '(' || c == '[' || c == '{') {
            stk.push(c);
        } else if (c == ')' || c == ']' || c == '}') {
            if (stk.empty()) {
                return false;  // No corresponding opening parenthesis in the stack
            }
            
            char top = stk.top();
            stk.pop();
            
            // Check if the current closing parenthesis matches the top of the stack
            if ((c == ')' && top != '(') || (c == ']' && top != '[') || (c == '}' && top != '{')) {
                return false;
            }
        }
    }
    
    return stk.empty();  // Stack should be empty if all parentheses are matched
}
