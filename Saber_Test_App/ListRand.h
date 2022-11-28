#ifndef LISTRAND_H
#define LISTRAND_H

#include <string>

namespace SaberInteractive_Test
{
	class ListRand
	{
	private:
		class ListNode
		{
		public:
			ListNode(const std::string& data = "", ListNode* pNext = nullptr, ListNode* pPrev = nullptr, ListNode* pRand = nullptr) :
				m_data(data),
				m_pNext(pNext),
				m_pPrev(pPrev),
				m_pRand(pRand)
			{}

			ListNode* m_pNext;
			ListNode* m_pPrev;
			ListNode* m_pRand;
			std::string m_data;
		};

		ListNode* m_head;
		ListNode* m_tail;
		int m_size;
		const std::string m_path;
		ListNode* get_random();

	public:
		ListRand();
		~ListRand();

		void Serialize(std::ofstream& fout);
		void Deserialize(std::ifstream& fin);

		void push_back(const std::string& data);
		int size() { return m_size; }
		void clear();

		ListNode* operator[](const int index);
	};
}

#endif 