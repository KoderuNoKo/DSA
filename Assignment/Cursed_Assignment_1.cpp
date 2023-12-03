#include "main.h"

class DLList;
class imp_res;

class DLList
{
protected:
	Restaurant::customer* head; // Dummy node
	Restaurant::customer* tail;
	Restaurant::customer* curr;
	int cnt;
	const int capacity;

	void init() {
		curr = head = tail = new Restaurant::customer("", 0, nullptr, nullptr);
		cnt = 0;
	}

	void removeAll()
	{
		while (head->next && head->next != head) {
			curr = head->next;
			head->next = head->next->next;
			delete curr;
		}
		head->next = nullptr;
		cnt = 0;
	}

public:
	DLList() : capacity(MAXSIZE) { init(); }

	virtual ~DLList() 
	{ 
		removeAll();
		delete head;
	}

	void clear() { removeAll(); init(); }

	virtual bool isSus(string name) = 0;

	int getLength() const { return cnt; }
	int getCapacity() const { return capacity; }
	bool isFull() const { return (cnt == capacity); }
	bool isEmpty() const { return (cnt == 0); }

	Restaurant::customer* getCustomer() const { return curr; }
};

struct CustomerStats
{
	string name;
	int energy;
	CustomerStats* next;
	CustomerStats(string name, int energy, CustomerStats* next) : name(name), energy(energy), next(next)
	{}
	CustomerStats()
	{
		name = "";
		energy = 0;
		next = nullptr;
	}
};

class CSQueue
{
	CustomerStats* head;
	CustomerStats* tail;
	int length;
public:
	CSQueue() : length(0)
	{
		head = new CustomerStats;
		tail = head;
	}
	~CSQueue()
	{
		CustomerStats* deleter = head;
		while (head)
		{
			deleter = head;
			head = head->next;
			delete deleter;
		}
	}
	void enqueue(CustomerStats* newCustomer)
	{ 
		newCustomer->next = nullptr;
		tail->next = newCustomer;
		tail = tail->next;
		if (length == 0) {
			head->next = tail;
		}
		length++;
	}
	void enqueue(string name, int energy)
	{
		tail->next = new CustomerStats(name, energy, nullptr);
		tail = tail->next;
		if (length == 0) {
			head->next = tail;
		}
		length++;
	}
	CustomerStats* dequeue()
	{
		if (length > 0)
		{
			CustomerStats* ret = head->next;
			head->next = head->next->next;
			length--;
			ret->next = nullptr;
			if (ret == tail) {
				tail = head;
			}
			length--;
			return ret;
		}
		else {
			return nullptr;
		}
	}

	void enqueueR(CustomerStats* newCustomer)
	{
		if (length == 0) {
			tail = newCustomer;
		}
		newCustomer->next = head->next;
		head->next = newCustomer;
	}

	CustomerStats* dequeueR()
	{
		if (length > 0)
		{
			CustomerStats* ret = tail;
			ret->next = nullptr;
			tail = head;
			while (tail->next != ret) {
				tail = tail->next;
			}
			tail->next = nullptr;
			if (tail == head) {
				head->next = nullptr;
			}
			length--;
			return ret;
		}
		else {
			return nullptr;
		}
	}
	CustomerStats* getValue() const { return head->next; }

	int getLength() const { return length; }
};


class imp_res : public Restaurant
{
	class DiningTable : public DLList
	{
	public:

		DiningTable()
		{
			init();
			head->next = head->prev = head;
		}

		void insert(string name, int energy)
		{
			if (head->next == head) //First insertion
			{ 
				head->next = new Restaurant::customer(name, energy, head, head);
				head->prev = head->next;
				curr = head->next;
			}
			else {
				curr->next = curr->next->prev = new Restaurant::customer(name, energy, curr, curr->next);
				curr = curr->next;
				if (curr == head) {
					curr = curr->next;
				}
			}
			cnt++;
		}

		void insert(Restaurant::customer* newCustomer)
		{
			if (head->next == head) 
			{
				newCustomer->prev = head;
				newCustomer->next = head;
				head->next = newCustomer;
				head->prev = head->next;
				curr = head->next;
			}
			else {
				newCustomer->prev = curr;
				newCustomer->next = curr->next;
				curr->next = curr->next->prev = newCustomer;
				curr = curr->next;
				if (curr == head) {
					curr = curr->next;
				}
			}
			cnt++;
		}

		void evict()
		{
			Restaurant::customer* deleter = curr;
			if (curr->energy > 0)
			{
				curr = curr->next;
				curr->prev = curr->prev->prev;
				curr->prev->next = curr;
				if (curr == head) {
					curr = curr->next;
				}
			}
			else
			{
				curr = curr->prev;
				curr->next = curr->next->next;
				curr->next->prev = curr;
				if (curr == head) {
					curr = curr->prev;
				}
			}
			cnt--;
			delete deleter;
		}

		void moveToStart() { curr = head->next; }
		void moveToEnd() { curr = head->prev; }
		void moveToPos(int index)
		{
			curr = head->next;
			for (int i = 0; i < index % cnt; i++) {
				curr = curr->next;
			}
		}
		void moveUp() 
		{
			curr = curr->next;
			if (curr == head) {
				curr = curr->next;
			}
		}
		void moveDown() 
		{ 
			curr = curr->prev; 
			if (curr == head) {
				curr = curr->prev;
			}
		}

		int getCurrPos() const
		{
			int pos = 0;
			Restaurant::customer* counter = head->next;
			while (counter != curr) {
				pos++;
				counter = counter->next;
			}
			return pos;
		}

		bool isSus(string name)
		{
			if (cnt == 0) {
				return false;
			}
			Restaurant::customer* checker = head->next;
			while (checker != head) {
				if (name == checker->name) {
					return true;
				}
				checker = checker->next;
			}
			if (name == checker->name) {
				return true;
			}
			return false;
		}

		void printTable()
		{
			Restaurant::customer* printer = head->next;
			for (int i = 0; i < this->getLength(); i++) {
				if (printer->energy == 0) {
					printer = printer->next;
				}
				cout << "<- "; printer->print(); cout << " ->";
				printer = printer->next;
			}
			cout << "\n";
		}
	};

	class WaitingLine : public DLList
	{
		int getRegOrder(const CSQueue*& customerOrder, string searchName) // come early -> low order value
		{
			CustomerStats* scanner = customerOrder->getValue();
			int regOrder = 0;
			while (scanner->name != searchName && scanner) {
				scanner = scanner->next;
				regOrder++;
			}

			if (!scanner) {
				return -1;
			}
			else {
				return regOrder;
			}
		}

		void moveToPos(int index)
		{
			curr = head->next;
			for (int i = 0; i < index % cnt; i++) {
				curr = curr->next;
			}
		}

		void swap(int i, int j)
		{
			this->moveToPos(i); // get info at i
			string tempNamei = curr->name;
			int tempEnergyi = curr->energy;
			this->moveToPos(j); // get info at j and change j
			string tempNamej = curr->name; 
			int tempEnergyj = curr->energy;
			curr->name = tempNamei;
			curr->energy = tempEnergyi;
			this->moveToPos(i); // change i
			curr->name = tempNamej;
			curr->energy = tempEnergyj;
		}

		void insertionSort(int start, int end, int incr, int& N, const CSQueue* customerOrder)
		{
			for (int i = start + incr; i < end + 1; i += incr) {
				for (int j = i; j >= incr; j -= incr) {
					this->moveToPos(j - incr);
					int energy1 = curr->energy;
					string name1 = curr->name;
					this->moveToPos(j);
					int energy2 = curr->energy;
					string name2 = curr->name;
					if (abs(energy1) > abs(energy2)) {
						break;
					}
					else if (abs(energy1) == abs(energy2) && this->getRegOrder(customerOrder, name1) < this->getRegOrder(customerOrder, name2)) {
						break;
					}
					swap(j, j - incr);
					N++;
				}
			}
		}

	public:
		WaitingLine() { init(); }

		void enterLine(string name, int energy)
		{
			tail->next = new Restaurant::customer(name, energy, tail, nullptr);
			tail = tail->next;
			cnt++;
		}

		void enterLine(Restaurant::customer* newCustomer)
		{
			newCustomer->prev = tail;
			newCustomer->next = nullptr;
			tail->next = newCustomer;
			tail = tail->next;
			cnt++;
		}

		Restaurant::customer* leaveLine()
		{
			if (this->getLength() == 0) {
				return nullptr;
			}
			Restaurant::customer* ret = head->next;
			head->next = head->next->next;
			if (head->next) {
				head->next->prev = head;
			}
			if (ret == tail) {
				tail = head;
			}
			cnt--;
			ret->next = nullptr;
			ret->prev = nullptr;
			return ret;
		}

		int shellSort(int start, int end, const CSQueue* customerOrder)
		{
			int N = 0;
			for (int i = end + 1 / 2; i > 2; i /= 2) {
				for (int j = 0; j < i; j++) {
					this->insertionSort(start, end - j, i, N, customerOrder);
				}
			}
			this->insertionSort(start, end, 1, N, customerOrder);
			return N;
		}

		Restaurant::customer* getFrontCus() { return head->next; }

		bool isSus(string name)
		{
			if (cnt == 0) {
				return false;
			}
			Restaurant::customer* checker = head->next;
			while (checker != tail) {
				if (name == checker->name) {
					return true;
				}
				checker = checker->next;
			}
			if (name == checker->name) {
				return true;
			}
			return false;
		}

		int getStrongestIdx()
		{
			int max = abs(tail->energy);
			Restaurant::customer* scanner = tail;
			while (scanner != head->next) {
				if (abs(scanner->energy) > max) {
					max = abs(scanner->energy);
				}
				scanner = scanner->prev;
			}
			int strongestIdx = cnt - 1;
			scanner = tail;
			while (scanner != head) {
				if (abs(scanner->energy) == max) {
					break;
				}
				scanner = scanner->prev;
				strongestIdx--;
			}
			return strongestIdx;
		}

		void printWaitingLine() {
			Restaurant::customer* printer = head->next;
			while (printer) {
				cout << "<- "; printer->print(); cout << " ->";
				printer = printer->next;
			}
			cout << endl;
		}
	};

	bool isGreater(int a, int b) { return (a > b); }
	bool isLess(int a, int b) { return (a < b); }

	DiningTable* diningTable;
	WaitingLine* waitingLine;
	CSQueue* customerOrder;

	void waitingLineToTable(Restaurant::customer* customer)
	{
		if (diningTable->isFull()) {
			return;
		}

		if (diningTable->isEmpty()) { //First customer
			diningTable->insert(customer);
		}
		else if (diningTable->getLength() < diningTable->getCapacity() / 2) // Standard
		{
			if (customer->energy < diningTable->getCustomer()->energy) {
				diningTable->moveDown();
			}
			diningTable->insert(customer);
		}
		else // Half full
		{
			int idx = 0;
			diningTable->moveToStart();
			int RES = abs(customer->energy - diningTable->getCustomer()->energy);
			for (int i = 1; i < diningTable->getLength(); i++)
			{
				diningTable->moveUp();
				if (RES < abs(customer->energy - diningTable->getCustomer()->energy)) {
					RES = abs(customer->energy - diningTable->getCustomer()->energy);
					idx = i;
				}
			}
			diningTable->moveToPos(idx);
			RES = customer->energy - diningTable->getCustomer()->energy;
			if (RES < 0) {
				diningTable->moveDown();
				diningTable->insert(customer);
			}
			else {
				diningTable->insert(customer);
			}
		}
	}

	public:	
		imp_res() 
		{
			diningTable = nullptr;
			waitingLine = nullptr;
			customerOrder = nullptr;
		};

		~imp_res()
		{
			if (diningTable)
				delete diningTable;
			if (waitingLine)
				delete waitingLine;
			if (customerOrder)
				delete customerOrder;
		}

		void RED(string name, int energy)
		{
			if (!diningTable) {
				diningTable = new DiningTable();
			}
			if (!waitingLine) {
				waitingLine = new WaitingLine();
			}
			if (!customerOrder) {
				customerOrder = new CSQueue();
			}
			//Restaurant::customer *cus = new customer (name, energy, nullptr, nullptr);
			if (energy == 0) {
				return;
			}
			if (diningTable->isSus(name) || waitingLine->isSus(name)) { //"thien thuong thien ha, duy nga doc ton"
				return;
			}

			if (!diningTable->isFull())
			{
				if (diningTable->isEmpty()) { // First customer
					diningTable->insert(name, energy);
				}
				else if (diningTable->getLength() < diningTable->getCapacity() / 2) // Standard
				{
					if (energy < diningTable->getCustomer()->energy) {
						diningTable->moveDown();
						diningTable->insert(name, energy);
					}
					else {
						diningTable->insert(name, energy);
					}
				}
				else // Half full
				{
					int idx = 0;
					diningTable->moveToStart();
					int RES = abs(energy - diningTable->getCustomer()->energy);
					for (int i = 1; i < diningTable->getLength(); i++) 
					{
						diningTable->moveUp();
						if (RES < abs(energy - diningTable->getCustomer()->energy)) {
							RES = abs(energy - diningTable->getCustomer()->energy);
							idx = i;
						}
					}
					diningTable->moveToPos(idx);
					RES = energy - diningTable->getCustomer()->energy;
					if (RES < 0) {
						diningTable->moveDown();
						diningTable->insert(name, energy);
					}
					else {
						diningTable->insert(name, energy);
					}
				}
				customerOrder->enqueue(name, energy);
			}
			else {
				if (waitingLine->isFull()) {
					return;
				}
				waitingLine->enterLine(name, energy);
				customerOrder->enqueue(name, energy);
			}
		}

		void BLUE(int num)
		{
			if (!diningTable) {
				diningTable = new DiningTable();
			}
			if (!waitingLine) {
				waitingLine = new WaitingLine();
			}
			if (!customerOrder) {
				customerOrder = new CSQueue();
			}
			for (int i = 0; i < num && diningTable->getLength() > 0; i++)
			{
				string oldestCustomer = customerOrder->getValue()->name;
				diningTable->moveToStart();
				while (diningTable->getCustomer()->name != oldestCustomer) {
					diningTable->moveUp();
				}
				diningTable->evict();
				CustomerStats* deleter = customerOrder->dequeue();
				delete deleter;
			}
			
			while (!waitingLine->isEmpty() && !diningTable->isFull()) {
				Restaurant::customer* temp = waitingLine->leaveLine();
				waitingLineToTable(temp);
			}
		}
		void PURPLE()
		{
			if (!diningTable) {
				diningTable = new DiningTable();
			}
			if (!waitingLine) {
				waitingLine = new WaitingLine();
			}
			if (!customerOrder) {
				customerOrder = new CSQueue();
			}
			if (waitingLine->getLength() == 0) {
				return;
			}
			int strongestIdx = waitingLine->getStrongestIdx();
			int N = waitingLine->shellSort(0, strongestIdx, customerOrder);
			BLUE(N % waitingLine->getCapacity());
		}
		void REVERSAL()
		{
			if (!diningTable) {
				diningTable = new DiningTable();
			}
			if (!waitingLine) {
				waitingLine = new WaitingLine();
			}
			if (!customerOrder) {
				customerOrder = new CSQueue();
			}
			bool (imp_res:: * comp)(int, int) = nullptr;
			CSQueue* customerHolder = new CSQueue();
			Restaurant::customer* marker = diningTable->getCustomer(); // X pos
			string Xname = marker->name;
			int Xenergy = marker->energy;

			for (int i = 0; i < 2; i++) //loop 2 times to reverse cursed spirits and sorcerers respectively
			{
					if (i == 0) { //loop 1, cursed spirits
						comp = (Xenergy < 0) ? &imp_res::isLess : &imp_res::isGreater;
					}
					if (i == 1) { //loop 2, sorcerers
						comp = (Xenergy < 0) ? &imp_res::isGreater : &imp_res::isLess;
					}
				
				
				// save the stats of customers
				if ( (this->*comp)(diningTable->getCustomer()->energy, 0) ) {
					customerHolder->enqueue(diningTable->getCustomer()->name, diningTable->getCustomer()->energy);
				}
				diningTable->moveDown();
				while (diningTable->getCustomer() != marker) {
					if ( (this->*comp)(diningTable->getCustomer()->energy, 0) ) {
						customerHolder->enqueue(diningTable->getCustomer()->name, diningTable->getCustomer()->energy);
					}
					diningTable->moveDown();
				}

				//reverse
				diningTable->moveUp();
				CustomerStats* temp = nullptr;
				while (diningTable->getCustomer() != marker && customerHolder->getLength() > 0) {
					if ((this->*comp)(diningTable->getCustomer()->energy, 0)) {
						temp = customerHolder->dequeue();
						diningTable->getCustomer()->name = temp->name;
						diningTable->getCustomer()->energy = temp->energy;
						delete temp;
					}
					diningTable->moveUp();
				}
				if ((this->*comp)(diningTable->getCustomer()->energy, 0) && customerHolder->getLength() > 0) {
					temp = customerHolder->dequeue();
					diningTable->getCustomer()->name = temp->name;
					diningTable->getCustomer()->energy = temp->energy;
					delete temp;
				}
			}
			while (diningTable->getCustomer()->name != Xname) {
				diningTable->moveUp();
			}
			delete customerHolder;
		}
		void UNLIMITED_VOID()
		{
			if (!diningTable) {
				diningTable = new DiningTable();
			}
			if (!waitingLine) {
				waitingLine = new WaitingLine();
			}
			if (!customerOrder) {
				customerOrder = new CSQueue();
			}
			if (diningTable->getLength() < 4) {
				return;
			}
			Restaurant::customer* scanner = diningTable->getCustomer();
			int posX = diningTable->getCurrPos(); // original X pos
			int minHolder = 0; // min Sum
			int currentSum = 0; // temp sum used during calculation
			int start = diningTable->getCurrPos(); // final result for start pos
			int end = (start + 4) % diningTable->getLength() + 1; // final result for end pos
			int startTemp = start, endTemp = end; //temp value used during calculation

			do
			{
				currentSum = 0;
				scanner = diningTable->getCustomer();
				for (int i = 0; i < 4; i++) 
				{
					if (scanner->energy == 0) { //skip dummy node
						i--;
						scanner = scanner->next;
						continue;
					}
					currentSum += scanner->energy;
					scanner = scanner->next;
				}

				while (endTemp != startTemp)
				{
					if (currentSum <= minHolder) { //update end and start
						minHolder = currentSum;
						end = endTemp;
						start = startTemp;
					}
					currentSum += scanner->energy;
					scanner = scanner->next;
					if (scanner->energy != 0) { //skip dummy node
						endTemp = (endTemp + 1) % diningTable->getLength();
					}
				}
				startTemp = (startTemp + 1) % diningTable->getLength();
				endTemp = (startTemp + 3) % diningTable->getLength();
				diningTable->moveUp();
			} while (startTemp != posX);
			diningTable->moveUp(); // restore curr ptr to X pos

			diningTable->moveToPos(start);
			scanner = diningTable->getCustomer();
			int tempSeqMinIdx = 0;
			for (int i = 1; i <= (end - start + diningTable->getLength()) % diningTable->getLength(); i++) { //find min in subsequence
				diningTable->moveUp();
				if (scanner->energy > diningTable->getCustomer()->energy) {
					scanner = diningTable->getCustomer();
					tempSeqMinIdx = i;
				}
			}
			tempSeqMinIdx = (tempSeqMinIdx + start) % diningTable->getLength();

			for (int i = 0; i <= (end - tempSeqMinIdx + diningTable->getLength()) % diningTable->getLength(); i++) { // print from min to end
				if (scanner->energy == 0) { //skip dummy node
					i--;
					scanner = scanner->next;
					continue;
				}
				scanner->print();
				scanner = scanner->next;
			}

			for (int i = 0; i <= (end - start + diningTable->getLength()) % diningTable->getLength(); i++) { // bring scanner back to start
				scanner = scanner->prev;
				if (scanner->energy == 0) {
					scanner = scanner->prev;
				}
			}

			for (int i = 0; i < (tempSeqMinIdx - start + diningTable->getLength()) % diningTable->getLength(); i++) {
				if (scanner->energy == 0) { //skip dummy node
					i--;
					scanner = scanner->next;
					continue;
				}
				scanner->print();
				scanner = scanner->next;
			}
			diningTable->moveToPos(posX);
		}
		
		void DOMAIN_EXPANSION()
		{
			if (!diningTable) {
				diningTable = new DiningTable();
			}
			if (!waitingLine) {
				waitingLine = new WaitingLine();
			}
			if (!customerOrder) {
				customerOrder = new CSQueue();
			}
			Restaurant::customer* scanner = diningTable->getCustomer();
			if (customerOrder->getLength() == 0) {
				return;
			}
			int totalEnergy = scanner->energy;
			scanner = scanner->next;
			while (scanner != diningTable->getCustomer()) { // calculate energy sum in table
				totalEnergy += scanner->energy;
				scanner = scanner->next;
			}
			scanner = waitingLine->getFrontCus();
			while (scanner != nullptr) { // total energy sum in table and waiting line
				totalEnergy += scanner->energy;
				scanner = scanner->next;
			}
			bool (imp_res:: * comp)(int, int) = nullptr;
			if (totalEnergy > 0) {
				comp = &imp_res::isLess; // evict all cursed spirits
			}
			else {
				comp = &imp_res::isGreater; // evict all jujutsu sorcerers
			}

			int lastXPos = diningTable->getCurrPos(); // save X pos 
			const int noCustomer = customerOrder->getLength();
			Restaurant::customer* printer = nullptr;
			for (int i = 0; i < noCustomer; i++)
			{
				CustomerStats* temp = customerOrder->dequeueR();
				if ( (this->*comp)(temp->energy, 0) ) {
					// Search for customer in table
					scanner = diningTable->getCustomer(); //use scanner as mark to stop iteration
					if (diningTable->getCustomer()->name == temp->name) {
						diningTable->evict();
						continue;
					}
					diningTable->moveUp();
					while (diningTable->getCustomer() != scanner) 
					{
						if (diningTable->getCustomer()->name == temp->name) {
							printer = diningTable->getCustomer();
							diningTable->evict();
							lastXPos = diningTable->getCurrPos();
							break;
						}
						diningTable->moveUp();
					}

					// Search for customer in waiting line
					Restaurant::customer* headOfLine = scanner = waitingLine->getFrontCus();
					if (waitingLine->isEmpty()) {
						continue;
					}
					headOfLine = headOfLine->prev; // get head of waiting line
					while (scanner)
					{
						if (scanner->name == temp->name) {
							// remove scanner from its pos
							if (scanner->next) {
								scanner->next->prev = scanner->prev;
							}
							scanner->prev->next = scanner->next;
							// place scanner to the head of waiting line
							scanner->next = headOfLine->next;
							scanner->prev = headOfLine;
							if (headOfLine->next) {
								headOfLine->next->prev = scanner;
							}
							headOfLine->next = scanner;
							//dequeue scanner
							printer = waitingLine->leaveLine();
							delete printer;
							break;
						}
						scanner = scanner->next;
					}
					delete temp;
				}
				else {
					customerOrder->enqueueR(temp);
				}
				diningTable->moveToPos(lastXPos);
			}
			while (!waitingLine->isEmpty() && !diningTable->isFull()) {
				Restaurant::customer* temp = waitingLine->leaveLine();
				waitingLineToTable(temp);
			}
		}
		void LIGHT(int num)
		{
			if (!diningTable) {
				diningTable = new DiningTable();
			}
			if (!waitingLine) {
				waitingLine = new WaitingLine();
			}
			if (!customerOrder) {
				customerOrder = new CSQueue();
			}
			Restaurant::customer* printer = nullptr;
			if (num > 0)
			{
				printer = diningTable->getCustomer();
				for (int i = 0; i < diningTable->getLength(); i++)
				{
					if (printer->energy == 0) {
						printer = printer->next;
					}
					printer->print();
					printer = printer->next;
				}
			}
			else if (num < 0)
			{
				printer = diningTable->getCustomer();
				for (int i = 0; i < diningTable->getLength(); i++)
				{
					if (printer->energy == 0) {
						printer = printer->prev;
					}
					printer->print();
					printer = printer->prev;
				}
			}
			else
			{
				Restaurant::customer* temp = nullptr;
				for (int i = 0; i < waitingLine->getLength(); i++) {
					temp = waitingLine->leaveLine();
					temp->print();
					waitingLine->enterLine(temp);
				}
			}
		}
};
