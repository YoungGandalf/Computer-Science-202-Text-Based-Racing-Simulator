/*
File:    Lqueue.h
Project: CMSC 202 Project 5, Fall 2018
Author:  Adam Hereth
Data:    12/5/2018
Section: 12
Email:   ahereth1@umbc.edu
*/

#include <string>
#include <iostream>
#include <iomanip>
#include <cmath>
using namespace std;

template <class T>
class Node {
public:
  Node( const T& data ); //Overloaded constructor
  T& GetData(); //Getter
  void SetData( const T& data ); //Setter
  Node<T>* GetNext(); //Getter
  void SetNext( Node<T>* next ); //Setter
private:
  T m_data; //Data stored in node
  Node<T>* m_next; //Pointer to next node
};

template <class T>
Node<T>::Node( const T& data ) {
   m_data = data;
   m_next = NULL;
}

template <class T>
T& Node<T>::GetData() {
   return m_data;
}

template <class T>
void Node<T>::SetData( const T& data ) {
   m_data = data;
}

template <class T>
Node<T>* Node<T>::GetNext() {
   return m_next;
}

template <class T>
void Node<T>::SetNext( Node<T>* next ) {
   m_next = next;
}

template <class T>
class Lqueue {
 public:
  // Name: Lqueue() (Linked List Queue) - Default Constructor
  // Desc: Used to build a new linked queue (as a linked list)
  // Preconditions: None
  // Postconditions: Creates a new lqueue where m_head and m_tail point to NULL
  Lqueue();
  // Name: ~Lqueue() - Destructor
  // Desc: Used to destruct a Lqueue
  // Preconditions: There is an existing lqueue with at least one node
  // Postconditions: An lqueue is deallocated (including dynamically allocated nodes)
  //                 to have no memory leaks!
 ~Lqueue();
  // Name: Lqueue (Copy Constructor)
  // Preconditions: Creates a copy of existing LQueue
  //                Requires a Lqueue
  // Postconditions: Copy of existing Lqueue
  Lqueue(const Lqueue&);
  // Name: operator= (Overloaded Assignment Operator)
  // Preconditions: Copies an Lqueue into an existing Lqueue
  //                Requires a Lqueue
  // Postconditions: Copy of existing Lqueue
  Lqueue<T>& operator = (Lqueue&);
  // Name: Push
  // Preconditions: Takes in data. Creates new node. 
  //                Requires a Lqueue
  // Postconditions: Adds a new node to the end of the lqueue.
  void Push(const T&);
  // Name: Pop
  // Preconditions: Lqueue with at least one node. 
  // Postconditions: Removes first node in the lqueue, returns data from first node.
  T Pop();
  // Name: Display
  // Preconditions: Outputs the lqueue.
  // Postconditions: Displays the data in each node of lqueue
  void Display();
  // Name: Front
  // Preconditions: Requires a populated lqueue
  // Postconditions: Returns whatever data is in front 
  T Front();
  // Name: IsEmpty
  // Preconditions: Requires a lqueue
  // Postconditions: Returns if the lqueue is empty.
  bool IsEmpty();
  // Name: GetSize
  // Preconditions: Requires a lqueue
  // Postconditions: Returns m_size
  int GetSize();
  // Name: Swap(int)
  // Preconditions: Requires a lqueue
  // Postconditions: Swaps the nodes at the index with the node prior to it.
  void Swap(int);
  // Name: Clear
  // Preconditions: Requires a lqueue
  // Postconditions: Removes all nodes in a lqueue
  void Clear();
  // Name: RemoveInsertEnd
  // Preconditions: Requires a lqueue
  // Postconditions: Moves a node from somewhere to the end of the lqueue
  void RemoveInsertEnd(int);
  // Name: TestHeadTail() (Optional test function)
  // Preconditions: Requires a lqueue
  // Postconditions: Returns the value of the head and the tail (used for main below)
  void TestHeadTail();
  // Name: operator<< (Overloaded << operator)
  // Preconditions: Requires a lqueue
  // Postconditions: Returns an ostream with the data from each node on different line
  template <class U>
  friend ostream& operator<<(ostream& output, const Lqueue<U>&);
  //Name: Overloaded [] operator
  //Precondition: Existing Lqueue
  //Postcondition: Returns object from Lqueue using []
  T& operator[] (int x);//Overloaded [] operator to pull data from Lqueue
private:
  Node <T> *m_head; //Node pointer for the head
  Node <T> *m_tail; //Node pointer for the tail
  int m_size; //Number of nodes in queue
};
//*********************************************************************
//******************Implement Lqueue Functions Here********************
template <class T>
Lqueue<T>::Lqueue()
{
  m_head = NULL;
  m_tail = NULL;
  m_size = 0;
}

template <class T>
Lqueue<T>::~Lqueue()
{
  Clear();
}

template <class T>
Lqueue<T>::Lqueue(const Lqueue& LLQ)
{
  //checks to see if the head from the queue is NULL
  if (LLQ.m_head == NULL)
    {
      m_head = NULL;
      m_tail = NULL;
    }
  else
    {
      //sets m_head to a new Node template which the parameters beings the LLQ's
      //data from getData
      m_head = new Node<T>(LLQ.m_head->GetData());
      Node<T>* temp1 = m_head;
      Node<T>* temp2 = LLQ.m_head;
      while (temp2->GetNext() != NULL)
	{
	  //sets temp1's next value to a new Node which is LLQ.m_head next nodes data
	  temp1->SetNext(new Node<T>(temp2->GetNext()->GetData()));
	  temp1 = temp1->GetNext();
	  temp2 = temp2->GetNext();
	}
      m_tail = temp1;
    }
}

template <class T>
Lqueue<T>& Lqueue<T>::operator = (Lqueue& LLQ)
{
  //checks to see if the memory address at LLQ does not equal this.
  if(&LLQ != this)
    {
      Clear();
      Node<T> *temp = LLQ.m_head;
      while(temp != NULL)
	{
	  Push(temp->GetData());
	  temp = temp->GetNext();
	}
    }
  return *this;
}

template <class T>
void Lqueue<T>::Push(const T& data)
{
  Node<T>* temp = new Node<T>(data);
  //have temp's next be NULL to get rid of any values
  temp->SetNext(NULL);
  if (m_head == NULL)
    {
      m_head = m_tail = temp;
      m_tail->SetNext(NULL);
    }
  else
    {
      m_tail->SetNext(temp);
      m_tail = temp;
      m_tail->SetNext(NULL);
    }
}

template <class T>
T Lqueue<T>::Pop()
{
  m_head = m_head->GetNext();
  return m_head->GetData();
}

template <class T>
void Lqueue<T>::Display()
{
  Node<T>* temp = m_head;
  if (temp == NULL)
    {
      cout << "list is empty" << endl;
    }
  if(temp->GetNext() == NULL)
    {
      cout << temp->GetData() << endl;
    }
  else
    {
      while (temp != NULL)
	{
	  cout << temp->GetData() << " ";
	  temp = temp->GetNext();
	}
      cout << endl;
    }
}

template <class T>
T Lqueue<T>::Front()
{
  return m_head->GetData();
}

template <class T>
bool Lqueue<T>::IsEmpty()
{
  if (m_head == NULL && m_tail == NULL)
    return true;
  else
    return false;
}

template <class T>
int Lqueue<T>::GetSize()
{
  if (m_head == NULL && m_tail == NULL)
    return 0;
  else
    {
      Node<T>* temp = m_head;
      int count = 0;
      while (temp != NULL)
	{
	  count++;
	  temp = temp->GetNext();
	}
      m_size = count;
      return m_size;
    }
}

template <class T>
void Lqueue<T>::Swap(int index)
{
  //creates 3 temp nodes
  Node<T>* temp1 = m_head;
  Node<T>* temp2 = m_head; 
  Node<T>* temp3 = m_head; 
  //case for when there are only 2 racers
  if(index == 1)
    {
      temp2=temp1->GetNext();
      temp3=temp2->GetNext();
      temp1->SetNext(temp3);
      temp2->SetNext(temp1);
      m_head = temp2;
    }
  //case for when there are only 3 racers
  else if(index == GetSize()-1)
    {
      for(int i=0;i < index - 2;i++)
	temp1 = temp1->GetNext();
      temp2 = temp1->GetNext();
      temp3 = temp2->GetNext();
      temp1->SetNext(temp3);
      temp2->SetNext(NULL);
      temp3->SetNext(temp2);
      m_tail = temp2;
    }
  //case for when there are 4 or more racers
  else
    {
      for (int i = 0; i < index - 2; i++)
	temp1 = temp1->GetNext();
      temp2 = temp1->GetNext();
      temp3 = temp2->GetNext();
      temp1->SetNext(temp3);
      temp2->SetNext(temp3->GetNext());
      temp3->SetNext(temp2);
    }
}

template <class T>
void Lqueue<T>::Clear()
{
  Node<T>* temp1 = m_head;
  Node<T>* temp2 = m_head;
  while(temp1 != NULL)
    {
      temp2 = temp1->GetNext();
      delete(temp1);
      temp1 = temp2;
    }
  m_head = NULL;
  m_tail = NULL;
  m_size = 0;
  
}

template <class T>
void Lqueue<T>::RemoveInsertEnd(int raceNum)
{
  Node<T>* temp1 = m_head;
  Node<T>* temp2 = m_head;
  if(m_head == NULL or m_head->GetNext() == NULL or raceNum > GetSize())
    {
      cout << "Empty" << endl;
    }
  //case for when there is only 1 racer
  else if(raceNum == 0)
    {
      m_head = m_head->GetNext();
      m_tail->SetNext(temp2);
      temp2->SetNext(NULL);
      m_tail=temp2;
    }
  //case for when there are 2 or more racers
  else
    {
      for(int i =0; i<raceNum-1;i++)
	temp1 = temp1->GetNext();
      temp2 = temp1->GetNext();
      temp1->SetNext(temp2->GetNext());
      m_tail->SetNext(temp2);
      temp2->SetNext(NULL);
      m_tail = temp2;
    }
}

template <class T>
void Lqueue<T>::TestHeadTail()
{
  cout << m_head->GetData() << endl;
  cout << m_tail->GetData() << endl;
}

template <class U>
ostream& operator<<(ostream& output, const Lqueue<U>& myLLQ)
{
  if(myLLQ.m_head)
    {
      Node<U> *temp = myLLQ.m_head;
      while(temp != NULL)
	{
	  output << temp->GetData() << "\n";
	  temp = temp->GetNext();
	}
    }
  else
    output << "List is empty";
  
  return output;
}

template <class T>
T& Lqueue<T>::operator[] (int x)
{
  int count = 0;
  Node<T> *tempCar = m_head;
  while(tempCar != NULL && count != x)
    {
      tempCar = tempCar->GetNext();
      count++;
    }
  return tempCar->GetData();
}

//************************Lqueue Tests Below***************************
// To test just Lqueue follow these instructions:
//   1.  mv Lqueue.h Lqueue.cpp
//   2.  Uncomment out int main below
//   3.  make Lqueue
//   4.  ./Lqueue

/*
int main () {
  //Test 1 - Default Constructor and Push
  cout << "Test 1 - Default Constructor and Push Running" << endl;
  //Test Default Constructor
  Lqueue <int> newLQ1;
  //Push 4 nodes into Lqueue
  newLQ1.Push(10);
  newLQ1.Push(11);
  newLQ1.Push(12);
  newLQ1.Push(13);
  cout << endl;
    
  //Test 2 - Copy Constructor and Assignment Operator
  cout << "Test 2 - Copy Constructor and Assignment Operator Running" << endl;
  //Test Copy constructor
  Lqueue <int> newLQ2(newLQ1);
  //Test Overloaded Assignment Operator
  Lqueue <int> newLQ3;
  newLQ3 = newLQ2;
  cout << endl;
  
  //Test 3 - Test Display and Overloaded <<
  cout << "Test 3 - Display and Overloaded << Running" << endl;
  cout << "newLQ1" << endl;
  newLQ1.Display();
  cout << "newLQ2" << endl;
  newLQ2.Display();
  cout << "newLQ3" << endl;
  newLQ3.Display();
  cout << "newLQ1" << endl;
  cout << newLQ1;
  cout << "newLQ2" << endl;
  cout << newLQ2;
  cout << "newLQ3" << endl;
  cout << newLQ3;
  cout << endl;
  
  //Test 4 - Test Front and Pop
  cout << "Test 4 - Front and Pop Running" << endl;
  //Test Front()
  cout << "Testing Front - Output 10" << endl;
  cout << newLQ1.Front() << endl;
  //Test Pop with Display of Pop
  cout << "Popping one node and displaying it" << endl;
  cout << newLQ1.Pop() << endl;
  //Test Pop with Display of Pop
  cout << "Popping one node and displaying it" << endl;
  cout << newLQ1.Pop() << endl;
  cout << endl;
  
  //Test 5 - Test GetSize and Clear
  cout << "Test 5 - GetSize and Clear Running" << endl;
  //Test GetSize()
  cout << "Outputting the size" << endl;
  cout << newLQ1.GetSize() << endl;
  //Test Clear()
  cout << "Clearing all nodes" << endl;
  newLQ1.Clear();
  cout << endl;
  
  //Test 6 - Test Swap
  cout << "Test 6 - Swap Running" << endl;
  newLQ2.Swap(2);
  cout << "Swap 2 - Should display 10->12->11->13->END" << endl;
  newLQ2.Display();
  //Testing to make sure head and tail point at the correct node
  newLQ2.TestHeadTail();
  cout << "Should display head 10 and tail 13" << endl;
  cout << endl;
  
  //Test 7 - Test RemoveInsertEnd(2)
  cout << "Test 7 - RemoveInsertEnd Running" << endl;
  cout << "Before RemoveInsertEnd" << endl;
  newLQ3.Display();
  newLQ3.TestHeadTail();
  newLQ3.RemoveInsertEnd(2);
  cout << "After RemoveInsertEnd 10->11->13->12->END" << endl;
  newLQ3.Display();
  newLQ3.TestHeadTail();
  
  return 0;
}
*/


