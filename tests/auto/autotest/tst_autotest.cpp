#include <QtTest>
#include <QDebug>
#include <QString>
#include <QDebug>
#include <QString>
#include "btree.h"

// add necessary includes here

class AutoTest : public QObject
{
    Q_OBJECT

public:
    AutoTest();
    ~AutoTest();

private slots:
    void test_avl()
    {
       auto root = btree::avl_insert(nullptr, 10);
        root = btree::avl_insert(root, 20);
        root = btree::avl_insert(root, 30);
        root = btree::avl_insert(root, 3);
        root = btree::avl_insert(root, 40);
        Q_ASSERT(root->val == 20);
        Q_ASSERT(root->right->val == 30);
        Q_ASSERT(root->right->right->val == 40);
        Q_ASSERT(root->left->val == 10);
        Q_ASSERT(root->left->left->val == 3);

        Q_ASSERT(btree::avl_search(root, 3) != nullptr);
        Q_ASSERT(btree::avl_search(root, 10) != nullptr);
        Q_ASSERT(btree::avl_search(root, 30) != nullptr);
        Q_ASSERT(btree::avl_search(root, 40) != nullptr);
        Q_ASSERT(btree::avl_search(root, 20) != nullptr);
        btree::avl_free(root);
    }

};

AutoTest::AutoTest()
{

}

AutoTest::~AutoTest()
{

}



QTEST_APPLESS_MAIN(AutoTest)

#include "tst_autotest.moc"
