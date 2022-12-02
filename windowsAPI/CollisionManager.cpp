#include "CollisionManager.h"
#include "SceneManager.h"
#include "Scene.h"
#include "GameObject.h"
#include "Collider.h"

namespace sw
{
    CollisionManager::CollisionManager()
    {

    }

    CollisionManager::~CollisionManager()
    {

    }

    void CollisionManager::Tick()
    {
        Scene* PlayScene = SceneManager::GetInstance()->GetPlayScene();

        for (int row = 0; row < COLLIDER_LAYER; row++)
        {
            for (int col = 0; col < COLLIDER_LAYER; col++)
            {
                if (mMatrix[row] & (1 << col))
                {
                    // �浹�� �Ǿ����� �ȵǾ������� �˻�
                    LayerCollision(PlayScene, (eColliderLayer)row, (eColliderLayer)col);
                }
            }
        }
    }

    std::vector<Collider*> CollisionManager::GetColliders(eColliderLayer type, Box box)
    {
        std::vector<Collider*> temp;

     
        Scene* scene = SceneManager::GetInstance()->GetPlayScene();
        std::vector<GameObject*>& objects = scene->GetGameObject(type);
        Box Box = box;

        for (GameObject* object : objects)
        {
            if (object == nullptr)
                break;

            Collider* collider = object->GetComponent<Collider>();
            if (Intersect(box, collider))
                temp.push_back(collider);
        }
        
        return temp;
    }

    void CollisionManager::SetLayer(eColliderLayer left, eColliderLayer right, bool value)
    {
        UINT row = 0;
        UINT col = 0;

        UINT iLeft = (UINT)left;
        UINT iRight = (UINT)right;

        if (iLeft < iRight)
        {
            row = (UINT)left;
            col = (UINT)right;
        }
        else
        {
            row = (UINT)right;
            col = (UINT)left;
        }

        if (value == true)
            mMatrix[row] |= (1 << col);
        else
            mMatrix[row] &= ~(1 << col);
    }

    void CollisionManager::LayerCollision(Scene* scene, eColliderLayer left, eColliderLayer right)
    {
        std::vector<GameObject*>& lefts = scene->GetGameObject(left);
        std::vector<GameObject*>& rights = scene->GetGameObject(right);

        for (auto leftObject : lefts)
        {
            Collider* leftCollider = leftObject->GetComponent<Collider>();
            if (leftCollider == nullptr)
                continue;

            for (auto rightObject : rights)
            {
                Collider* rightCollider = rightObject->GetComponent<Collider>();

                if (rightCollider == nullptr)
                    continue;

                if (leftObject == rightObject)
                    continue;

                ColliderCollision(leftCollider, rightCollider);
            }
        }
    }

    void CollisionManager::ColliderCollision(Collider* left, Collider* right)
    {
        // �� �浹ü�� Layer ��ȣ�� �ϴ� Ȯ�����ش�
        ColliderID id(left->GetID(), right->GetID());

        std::map<UINT64, bool>::iterator iter
            = mCollisionInformation.find(id.ID);

        // �浹������ ���ٸ� �浹������ �������ش�.
        if (iter == mCollisionInformation.end())
        {
            mCollisionInformation.insert(std::make_pair(id.ID, false));
            iter = mCollisionInformation.find(id.ID);
        }

        if (Intersect(left, right))
        {
            // ���� ��
            if (iter->second == false)
            {
                // ���� �ѹ� �浹

                // �浹�Լ��� ȣ�����ָ�ȴ�.
                // OnCollisionEneter();
                left->OnCollisionEnter(right);
                right->OnCollisionEnter(left);

                iter->second = true;
            }
            else
            {
                // �浹 ���϶�
                // OnCollisionStay();
                left->OnCollisionStay(right);
                right->OnCollisionStay(left);
            }
        }
        else
        {
            // �浹 x
            if (iter->second)
            {
                left->OnCollisionExit(right);
                right->OnCollisionExit(left);

                iter->second = false;
            }
        }
    }

    bool CollisionManager::Intersect(Collider* left, Collider* right)
    {
        if (left->GetOwner()->IsDeath())
            return false;
        if (right->GetOwner()->IsDeath())
            return false;

        Vector2 leftPos = left->GetPos();
        Vector2 leftScale = left->GetScale();


        Vector2 rightPos = right->GetPos();
        Vector2 rightScale = right->GetScale();

        if (fabs(leftPos.x - rightPos.x) < fabs(leftScale.x / 2.0f + rightScale.x / 2.0f)
            && fabs(leftPos.y - rightPos.y) < fabs(leftScale.y / 2.0f + rightScale.y / 2.0f))
        {
            return true;
        }

        return false;
    }

    bool CollisionManager::Intersect(Box box, Collider* right)
    {
        if (right->GetOwner()->IsDeath())
            return false;

        Vector2 BoxPos = box.BoxPos;
        Vector2 BoxScale = box.BoxScale;


        Vector2 rightPos = right->GetPos();
        Vector2 rightScale = right->GetScale();

        if (fabs(BoxPos.x - rightPos.x) < fabs(BoxScale.x / 2.0f + rightScale.x / 2.0f)
            && fabs(BoxPos.y - rightPos.y) < fabs(BoxScale.y / 2.0f + rightScale.y / 2.0f))
        {
            return true;
        }

        return false;
    }
}