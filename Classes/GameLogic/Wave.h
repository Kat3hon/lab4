class Wave {
public:
    explicit Wave(unsigned int enemyCount, unsigned int enemySpawnInterval = 100);

    // Amount of enemies this wave will contain
    unsigned int getEnemyCount();

    // This is in milliseconds
    unsigned int getEnemySpawnInterval();

    // To keep track to how many enemies have been spawned of the maximum amount of this wave
    void enemyGotSpawned();

private:
    unsigned int m_enemiesSpawned;
    unsigned int m_enemyCount;
    unsigned int m_enemySpawnInterval;
};
