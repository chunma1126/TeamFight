# TeamFight

<aside>


> 📌 현재 개발중인 턴제 게임입니다.

</aside>

<p align="ㅣㄷㄽ">
  <img src="Image/스크린샷_1.png" alt="스크린샷1" width="270"/>
  <img src="Image/스크린샷_2.png" alt="스크린샷2" width="270"/>
</p>

🔗 [유튜브](https://youtu.be/XXkLlENpVm4)  
🔗 [문서](https://url.kr/64a7ni)  

| 항목 | 내용 |
| --- | --- |
| 🎮 게임 이름 | **Team Fight** |
| 🕹 장르 | 턴제 RPG |
| 🛠 사용 기술 | Cocos2d-x, C++ |
| 👤 역할 | 개인 개발 |
| 📅 개발 기간 | 2025.05.31 ~ 진행 중 |
| 👥 개발 인원 | 1명 |


## ✅ 수행한 역할

### 🔹 시스템 개발
- `BattleManager`를 통해 TeamController,TurnController,CommandController등둥 핵심 시스템들을 관리.
- `Command Pattern`을 적용하여 Entity들의 행동을 유연하고 확장성 있게 순차 실행.
- `StatController`를 통해 체력, 공격력 등 스탯을 체계적으로 관리.
- `Observer Pattern`을 활용해 `Level`, `GameOver`, `UI 상태 변화` 등을 이벤트 기반으로 처리.

### 🔹 콘텐츠 개발
- Knight, Archer, Pawn 등 각각의 고유 스킬을 가진 Entity 개발.
- 다양한 SpriteSheet에 대응 가능한 범용 `Animator` 시스템 설계 및 구현.
- 레벨 완료 시 보상을 표시하고, 올바른 스프라이트가 출력되도록 시트 연동 처리.

### 🔹 기타 시스템
- `TileMap`을 활용한 배경 구성 및 무한 스크롤링 구현.
- 기본 UI 버튼을 상속한 `JYDButton`을 제작하여 UI 이벤트 확장에 활용.

---

### 🔹 주요 시스템 구성

#### ✅ 턴 및 커맨드 처리 (TurnController, CommandController)
- 턴 흐름을 `TurnController`가 관리하며 `CommandController`에서 각 Entity의 행동들의 흐름을 관리 합니다.
- 각 행동은 `Command` 추상클래스로 추상화되어 있으며, 실행 큐에 등록되어 순차적으로 실행됩니다.
- 턴 종료 시 다음으로 `SPD`스탯이 높은 Entity에게 자동으로 넘어갑니다.

#### ✅ 스탯 시스템 (StatController)
- 각 Entity는 고유한 `StatController`를 가지고 있으며, 체력, 마나, 공격력 등의 스탯을 중앙에서 관리합니다.
- 각 스탯의 값이 변할때 이벤트가 발생할수 있게 

#### ✅ 애니메이션 시스템 (Animator)
- 다양한 SpriteSheet에 대응할 수 있도록 범용 애니메이션 시스템을 설계했습니다.
- State기반으로 Animation의 상태를 관리했습니다.

#### ✅ 옵저버 패턴
- 레벨 종료, 체력 0, 특정 이벤트 발생 등은 `Observer` 패턴으로 처리되어 **비동기적**이고 **모듈화된 로직**을 구성합니다.
- 예: `CommandController`는 클리어 조건을 만족하면 `OnLevelClear` 이벤트를 구독자에게 전달합니다.

#### ✅ UI
- `JYDButton`은 기존 Cocos 버튼을 확장한 커스텀 UI 컴포넌트입니다.
- 클릭 이벤트 외에도 Hover이벤트들을 등록하고 자유롭게 Sprite들을 바꿀수 있게 확장했습니다.

---