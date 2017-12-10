#include "include/gameEngine/music_player.h"

MusicPlayer::MusicPlayer()
        : mMusic()
        , mFileNames()
        , mVolume(100.f)
{
    mFileNames[Music::Test] = "assets/music/test.wav";
    mFileNames[Music::Menu] = "assets/music/menu.ogg";
    mFileNames[Music::GameOver] = "assets/music/game_over.ogg";

}

void MusicPlayer::play(Music::ID theme)
{
    std::string filename = mFileNames[theme];

    if (!mMusic.openFromFile(filename))
        throw std::runtime_error("Music " + filename + ": failed to open");

    mMusic.setVolume(mVolume);
    mMusic.setLoop(true);
    mMusic.play();
}

void MusicPlayer::stop()
{
    mMusic.stop();
}

void MusicPlayer::setPaused(bool paused)
{
    if (paused)
        mMusic.pause();
    else
        mMusic.play();
}

void MusicPlayer::setVolume(float volume)
{
    mVolume = volume;
    mMusic.setVolume(volume);
}
