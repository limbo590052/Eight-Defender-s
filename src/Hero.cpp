#include "Hero.hpp"
#include "JobDatabase.hpp"
#include "config.hpp"

Hero::Hero(const std::string& jobName, glm::vec2 pos) : m_JobName(jobName) {
    m_JobType = StringToJob(jobName);
    m_Transform.translation = pos;
    SetZIndex(30.0f);

    if (JobDatabase.count(m_JobType)) {
        m_Stats = JobDatabase[m_JobType];
    }

    // Bar
    m_AttackBar = std::make_shared<ProgressBar>(
            RESOURCE_DIR "/UI/BarBG.png",
            RESOURCE_DIR "/UI/RedFill.png",
            pos + glm::vec2{5.f, -15.f}
    );

    m_RestBar = std::make_shared<ProgressBar>(
            RESOURCE_DIR "/UI/BarBG.png",
            RESOURCE_DIR "/UI/YellowFill.png",
            pos + glm::vec2{5.f, -10.f}
    );
    m_AttackBar->SetZIndex(this->GetZIndex()+ 1.1f);
    m_RestBar->SetZIndex(this->GetZIndex()+ 1.1f);


    // 角色圖
    auto imagePath = RESOURCE_DIR "/Jobs/" + jobName + ".png";
    m_Sprite = std::make_shared<Util::GameObject>();
    m_Sprite->SetDrawable(std::make_shared<Util::Image>(imagePath));
    m_Sprite->SetZIndex(this->GetZIndex() + 1.0f);
    m_Sprite->m_Transform.scale = {1.25f, 1.25f};
    m_Sprite->m_Transform.translation = pos + glm::vec2{0.0f, 60.0f};
    LOG_DEBUG("Hero Pos: ({}, {})", pos.x, pos.y);
    LOG_DEBUG("m_Sprite Pos: ({}, {})", m_Sprite->m_Transform.translation.x, m_Sprite->m_Transform.translation.y);
    LOG_DEBUG("AttackBar Pos: ({}, {})", m_AttackBar->m_Transform.translation.x, m_AttackBar->m_Transform.translation.y);
    LOG_DEBUG("AttackBar ZIndex: {}", m_AttackBar->GetZIndex());

    // 2. 初始化攻擊特效動畫
    std::vector<std::string> effectPaths = {
            RESOURCE_DIR "/Jobs/" + jobName + ".png"
    };

    // 將動畫保存到成員變數，避免使用 GetDrawable()
    auto ani = std::make_shared<Util::Animation>(effectPaths, false, 100, false, 0);
    m_AnimationLoop = ani; // <--- 建議在 .hpp 宣告這個變數

    m_AttackEffect = std::make_shared<Util::GameObject>();
    m_AttackEffect->SetDrawable(ani);
    m_AttackEffect->SetVisible(false);
    m_AttackEffect->SetZIndex(0.1f);
    AddChild(m_AttackEffect);

    m_AttackBar->SetProgress(1.0f);
}
void Hero::PlayAttackAnimation() {
    if (m_IsAttacking) return;

    m_IsAttacking = true;
    m_AttackEffect->SetVisible(true);

    // 直接使用保存好的動畫指標
    m_AnimationLoop->Play();
}

void Hero::Update() {
    // 檢查動畫狀態
    // 注意：請確認你的框架中 State 的成員名。
    // 如果 STOP 不行，試試 ENDED 或利用 IsPlaying() 判斷
    if (m_IsAttacking && m_AnimationLoop->GetState() == Util::Animation::State::ENDED) {
        m_IsAttacking = false;
        m_AttackEffect->SetVisible(false);
    }
}

void Hero::Draw() {
    m_Sprite->Draw();
    m_AttackBar->Draw();
    m_RestBar->Draw();
}