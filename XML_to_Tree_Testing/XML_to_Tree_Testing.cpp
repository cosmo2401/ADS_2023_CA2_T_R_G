#include "pch.h"
#include "CppUnitTest.h"
#include "../CA2_XML_to_Tree/TreeFunctions.h"



using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace XMLtoTreeTesting
{
	TEST_CLASS(XMLtoTreeTesting)
	{
	public:
		//Tests for readFile
		TEST_METHOD(TestFilePathValid)
		{
			string xml = readFile("../nothing.txt");
			string nothing = "";
			Assert::AreEqual(nothing, xml);
		}
		TEST_METHOD(TestFilePathInValid)
		{
			string xml = readFile("xml.xml");
			string nothing = "";
			Assert::AreNotEqual(nothing, xml);
		}
		//Tests for Validate XML
		TEST_METHOD(TestXMLValid)
		{
			string xml = "<dir><name>test</name><dir><name>subTest</name></dir></dir>";
			Assert::IsTrue(valdiateXML(xml));
		}
		TEST_METHOD(TestXMLInValid)
		{
			string xml = "<dir>test</name<dir><name>subTest></dir</dir";
			Assert::IsFalse(valdiateXML(xml));
		}
		//Tests for buildTree
		TEST_METHOD(TestBuildTreeValid)
		{
			string xml = "<dir><name>test</name><dir><name>subTest</name></dir></dir>";

			Tree<xmlData>* xmlTree = createTree(xml);

			Assert::IsNotNull(xmlTree);
		}
		TEST_METHOD(TestBuildTreeEmpty)
		{
			string empty = "";
			Tree<xmlData>* xmlTree = createTree(empty);

			Assert::IsNull(xmlTree);
		}
		TEST_METHOD(TestBuildTreeNoRoot)
		{
			string xml = "<name>test</name><dir><name>subTest</name></dir></dir>";

			Tree<xmlData>* xmlTree = createTree(xml);

			Assert::IsNull(xmlTree);
		}
		// Test for Count Folder
		TEST_METHOD(TestCountFolders)
		{
			string xml = "<dir><name>test</name><dir><name>subTest</name></dir></dir>";

			Tree<xmlData>* xmlTree = createTree(xml);
			TreeIterator<xmlData> treeIter(xmlTree);

			Assert::AreEqual(2, countFolders(treeIter));
		}
		// Test for Count Files
		TEST_METHOD(TestCountFilesValid)
		{
			string xml = "<dir><name>test</name><dir><name>subTest</name><file><name>config</name><length>353 b</length><ype>config</type></file></dir></dir>";

			Tree<xmlData>* xmlTree = createTree(xml);
			TreeIterator<xmlData> treeIter(xmlTree);

			Assert::AreEqual(1, countFiles(treeIter));
		}
		TEST_METHOD(TestCountFilesNoFiles)
		{
			string xml = "<dir><name>test</name><dir><name>subTest</name></dir></dir>";

			Tree<xmlData>* xmlTree = createTree(xml);
			TreeIterator<xmlData> treeIter(xmlTree);

			Assert::AreEqual(0, countFiles(treeIter));
		}
		// Test for Count
		TEST_METHOD(TestCount)
		{
			string xml = "<dir><name>test</name><dir><name>subTest</name><file><name>config</name><length>353 b</length><ype>config</type></file></dir></dir>";

			Tree<xmlData>* xmlTree = createTree(xml);

			Assert::AreEqual(3, xmlTree->count());
		}
		// Tests for calculate memory used
		TEST_METHOD(TestCalceMemoryUsedWithMemory)
		{
			string xml = "<dir><name>test</name><dir><name>subTest</name><file><name>config</name><length>353 b</length><ype>config</type></file></dir></dir>";

			Tree<xmlData>* xmlTree = createTree(xml);
	
			Assert::AreEqual(353, calcMemoryUsed(*xmlTree));
		}
		TEST_METHOD(TestCalceMemoryUsedWithoutMemory)
		{
			string xml = "<dir><name>test</name><dir><name>subTest</name></dir></dir>";

			Tree<xmlData>* xmlTree = createTree(xml);
	
			Assert::AreEqual(0, calcMemoryUsed(*xmlTree));
		}
		// Test 
		TEST_METHOD(TestFindPartialString)
		{
			string xml = "<dir><name>test</name><dir><name>subTest</name></dir></dir>";

			Tree<xmlData>* xmlTree = createTree(xml);
			TreeIterator<xmlData> treeIter(xmlTree);

			// No clue on how to est this one
		}

	};
}
