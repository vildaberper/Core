#pragma once

template <typename T>
class Queue{

private:

	template <typename T>
	class Node{
	public:
		Node<T>* next;
		Node<T>* previous;
		const T value;

		Node(Node<T>* next, Node<T>* previous, const T& value):
			next(next), previous(previous), value(value){
		}

		~Node(){ }
	};

	Node<T>* head_;
	Node<T>* tail_;
	size_t size_;

public:

	Queue(){
		head_ = nullptr;
		tail_ = nullptr;
		size_ = 0;
	}

	~Queue(){
		clear();
	}

	bool empty() const{
		return size_ == 0;
	}

	size_t size() const{
		return size_;
	}

	void clear(){
		while(head_ != nullptr){
			Node<T>* tmp = head_->next;
			delete head_;
			head_ = tmp;
		}
		size_ = 0;
	}

	T head() const{
		return head_->value;
	}

	T tail() const{
		return tail_->value;
	}

	T pop_head(){
		T e = head_->value;
		Node<T>* next = head_->next;

		delete head_;
		head_ = next;
		if(head_ == nullptr) tail_ = nullptr;
		else head_->previous = nullptr;
		--size_;

		return e;
	}

	T pop_tail(){
		T e = tail_->value;
		Node<T>* previous = tail_->previous;
		
		delete tail_;
		tail_ = previous;

		if(tail_ == nullptr) head_ = nullptr;
		else tail_->next = nullptr;
		--size_;

		return e;
	}

	void push_front(const T& e){
		Node<T>* t = new Node<T>(nullptr, nullptr, e);

		if(head_ == nullptr) tail_ = head_ = t;
		else{
			head_->previous_ = t;
			t->next = head_;
			head_ = t;
		}
		++size_;
	}

	void push_back(const T& e){
		Node<T>* t = new Node<T>(nullptr, nullptr, e);

		if(tail_ == nullptr) head_ = tail_ = t;
		else{
			tail_->next = t;
			t->previous = tail_;
			tail_ = t;
		}
		++size_;
	}

};
