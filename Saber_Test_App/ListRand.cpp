#include <iostream>
#include <fstream>
#include <string>
#include <unordered_map>
#include "ListRand.h"
#include "SimpleTimer.h"

namespace SaberInteractive_Test 
{
	ListRand::ListRand() :
		m_head(nullptr),
		m_tail(nullptr),
		m_size(0),
		m_path("storage.txt")
	{}

	ListRand::~ListRand()
	{
		clear();
	}

	void ListRand::push_back(const std::string& data)
	{
		if (m_head == nullptr)
		{
			m_head = new ListNode(data);
			m_tail = m_head;
		}
		else
		{
			ListNode* newNode = new ListNode(data);
			m_tail->m_pNext = newNode;
			newNode->m_pPrev = m_tail;
			m_tail = newNode;
			m_tail->m_pRand = get_random();
		}
		m_size++;
	}


	ListRand::ListNode* ListRand::get_random()
	{
		int randomIndex = std::rand() % size() + 1;

		if (randomIndex != size())
			return this->operator[](randomIndex);
		else
			return nullptr;
	}

	void ListRand::clear()
	{
		while (m_size)
		{
			if (m_size == 1)
			{
				delete m_head;
				m_head = m_tail = nullptr;
			}
			else
			{
				ListNode* toDelete = m_tail;
				m_tail = m_tail->m_pPrev;
				m_tail->m_pNext = nullptr;

				delete toDelete;
			}
			m_size--;
		}
	}

	ListRand::ListNode* ListRand::operator[](const int index)
	{
		int counter;
		ListNode* curr;

		if (index < m_size / 2)
		{
			counter = 0;
			curr = m_head;

			while (counter != index)
			{
				curr = curr->m_pNext;
				counter++;
			}
			return curr;
		}
		else
		{
			counter = m_size - 1;

			curr = m_tail;

			while (counter != index)
			{
				curr = curr->m_pPrev;
				counter--;
			}
			return curr;
		}
	}

	void ListRand::Serialize(std::ofstream& fout)
	{
		if (m_size <= 0)
		{
			std::cout << "list is empty" << std::endl;
			return;
		}

		std::cout << "Serialization started" << std::endl;

		SimpleTimer timer;

		std::unordered_map<ListNode*, int> storage;
		int id = 0;

		for (ListNode* node = m_head; node != m_tail; node = node->m_pNext)
		{
			storage[node] = id;
			id++;
		}

		fout.open(m_path);

		if (!fout.is_open())
		{
			std::cout << "Cannot open file" << std::endl;
			return;
		}

		for (ListNode* node = m_head; node; node = node->m_pNext)
		{
			fout << node->m_data << " ";

			if (node->m_pRand != nullptr)
				fout << storage[node->m_pRand] << " ";
			else
				fout << "-1 ";
		}

		fout.close();
	}

	void ListRand::Deserialize(std::ifstream& fin)
	{
		std::cout << "Deserialization started" << std::endl;

		SimpleTimer timer;

		if (m_size > 0)
			clear();

		std::unordered_map<int, std::pair<ListNode*, int>> storage;

		fin.open(m_path);

		if (!fin.is_open())
		{
			std::cout << "Cannot open file" << std::endl;
			return;
		}

		int counter = 0;

		while (!fin.eof())
		{
			std::string data;
			std::string index;

			fin >> data;
			fin >> index;

			if (index != "")
			{
				storage[counter] = std::make_pair(new ListNode(data), std::stoi(index));
				counter++;
			}
		}

		m_size = counter;

		if (storage.empty())
		{
			std::cout << "File is empty" << std::endl;
			return;
		}

		m_head = m_tail = storage[0].first;
		ListNode* curr = m_head;
		int randomIndex = storage[0].second;
		curr->m_pRand = randomIndex != -1 ? storage[randomIndex].first : nullptr;

		if (m_size > 1)
		{
			curr->m_pNext = storage[1].first;

			for (int i = 1; i < m_size; i++)
			{
				curr = storage[i].first;

				randomIndex = storage[i].second;
				curr->m_pRand = randomIndex != -1 ? storage[randomIndex].first : nullptr;

				if (i != m_size - 1)
				{
					curr->m_pNext = storage[i + 1].first;
					curr->m_pPrev = storage[i - 1].first;
				}
				else
				{
					curr->m_pNext = nullptr;
					curr->m_pPrev = storage[i - 1].first;
					m_tail = curr;
				}
			}
		}

		fin.close();
	}
}

