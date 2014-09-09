require "AudioEngine" 

audio = AudioEngine

return audio
--[[
    AudioEngine.playMusic(MUSIC_FILE, true)
    AudioEngine.stopMusic()
    AudioEngine.pauseMusic()
    AudioEngine.resumeMusic()
    AudioEngine.rewindMusic()
    AudioEngine.isMusicPlaying()
    AudioEngine.playEffect(EFFECT_FILE)
    m_nSoundId = AudioEngine.playEffect(EFFECT_FILE, true)
    AudioEngine.stopEffect(m_nSoundId)
    AudioEngine.unloadEffect(EFFECT_FILE)
    AudioEngine.setMusicVolume(AudioEngine.getMusicVolume() + 0.1)
    AudioEngine.setMusicVolume(AudioEngine.getMusicVolume() - 0.1)
    AudioEngine.setEffectsVolume(AudioEngine.getEffectsVolume() + 0.1)
    AudioEngine.setEffectsVolume(AudioEngine.getEffectsVolume() - 0.1)
    AudioEngine.pauseEffect(m_nSoundId)
    AudioEngine.resumeEffect(m_nSoundId)
    AudioEngine.pauseAllEffects()
    AudioEngine.resumeAllEffects()
    AudioEngine.stopAllEffects()
--]]
