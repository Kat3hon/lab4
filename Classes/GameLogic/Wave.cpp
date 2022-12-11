#include "Wave.h"

Wave::Wave(unsigned int enemyCount, unsigned int enemySpawnInterval) : m_enemyCount(enemyCount),
                                                                       m_enemySpawnInterval(enemySpawnInterval),
                                                                       m_enemiesSpawned(0) {

}

unsigned int Wave::getEnemyCount() {
    return m_enemyCount - m_enemiesSpawned;
}

unsigned int Wave::getEnemySpawnInterval() {
    return m_enemySpawnInterval;
}

void Wave::enemyGotSpawned() {
    m_enemiesSpawned++;
}