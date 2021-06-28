#include <list>
#include <string>
#include "test_runner.h"
using namespace std;

class Editor {
private:
	list<char> m_text;
	list<char>::iterator m_cursor;
	list<char> m_buffer;

public:
	// Реализуйте конструктор по умолчанию и объявленные методы
	Editor() : m_cursor(m_text.begin()) {}

	void Left() {
		if (m_cursor != m_text.begin()) {
			m_cursor = prev(m_cursor);
		}
	}

	void Right() {
		if (m_cursor != m_text.end()) {
			m_cursor = next(m_cursor);
		}
	}

	void Insert(char token) {
		m_cursor = next(m_text.insert(m_cursor, token));
	}

	void Cut(size_t tokens = 1) {
		m_buffer.clear();
		while (tokens != 0 && m_cursor != m_text.end()) {
			auto cut_it = m_cursor;
			m_cursor = next(m_cursor);
			tokens--;
			m_buffer.splice(m_buffer.end(), m_text, cut_it);
		}
	}

	void Copy(size_t tokens = 1) {
		m_buffer.clear();
		auto copy_it = m_cursor;
		while (tokens != 0 && copy_it != m_text.end()) {
			tokens--;
			m_buffer.push_back(*copy_it);
			copy_it = next(copy_it);
		}
	}

	void Paste() {
		m_text.insert(m_cursor, m_buffer.begin(), m_buffer.end());
	}

	string GetText() const {
		return {m_text.begin(), m_text.end()};
	}
};

void TypeText(Editor& editor, const string& text) {
	for(char c : text) {
		editor.Insert(c);
	}
}

void TestEditing() {
	{
		Editor editor;

		const size_t text_len = 12;
		const size_t first_part_len = 7;
		TypeText(editor, "hello, world");
		for(size_t i = 0; i < text_len; ++i) {
			editor.Left();
		}
		editor.Cut(first_part_len);
		for(size_t i = 0; i < text_len - first_part_len; ++i) {
			editor.Right();
		}
		TypeText(editor, ", ");
		editor.Paste();
		editor.Left();
		editor.Left();
		editor.Cut(3);

		ASSERT_EQUAL(editor.GetText(), "world, hello");
	}
	{
		Editor editor;

		TypeText(editor, "misprnit");
		editor.Left();
		editor.Left();
		editor.Left();
		editor.Cut(1);
		editor.Right();
		editor.Paste();

		ASSERT_EQUAL(editor.GetText(), "misprint");
	}
}

void TestReverse() {
	Editor editor;

	const string text = "esreveR";
	for(char c : text) {
		editor.Insert(c);
		editor.Left();
	}

	ASSERT_EQUAL(editor.GetText(), "Reverse");
}

void TestNoText() {
	Editor editor;
	ASSERT_EQUAL(editor.GetText(), "");

	editor.Left();
	editor.Left();
	editor.Right();
	editor.Right();
	editor.Copy(0);
	editor.Cut(0);
	editor.Paste();

	ASSERT_EQUAL(editor.GetText(), "");
}

void TestEmptyBuffer() {
	Editor editor;

	editor.Paste();
	TypeText(editor, "example");
	editor.Left();
	editor.Left();
	editor.Paste();
	editor.Right();
	editor.Paste();
	editor.Copy(0);
	editor.Paste();
	editor.Left();
	editor.Cut(0);
	editor.Paste();

	ASSERT_EQUAL(editor.GetText(), "example");
}

int main() {
	TestRunner tr;
	RUN_TEST(tr, TestEditing);
	RUN_TEST(tr, TestReverse);
	RUN_TEST(tr, TestNoText);
	RUN_TEST(tr, TestEmptyBuffer);
	return 0;
}
