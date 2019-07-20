//
// Created by Michael on 2019-07-19.
//

#include "AudioEngine.h"
#include "../../../../../oboe/src/common/OboeDebug.h"
#include "Constants.h"
#include "AAssetDataSource.h"

AudioEngine::AudioEngine(AAssetManager &assetManager): mAssetManager(assetManager) {
}


void AudioEngine::play() {

}

bool AudioEngine::setupSource() {

    // Set the properties of our audio source(s) to match that of our audio stream
    AudioProperties targetProperties{
            .channelCount = mAudioStream->getChannelCount(),
            .sampleRate = mAudioStream->getSampleRate()
    };


    // Create a data source and player for our backing track
    std::shared_ptr<AAssetDataSource> loopSource{
            AAssetDataSource::newFromCompressedAsset(mAssetManager, loopFileName, targetProperties)
    };
    if (loopSource == nullptr) {
        LOGE("Could not load source data for backing track");
        return false;
    }
    loop = std::make_unique<Player>(loopSource);
    loop->setPlaying(true);
    loop->setLooping(true);

    // Add both players to a mixer

    mMixer.addTrack(loop.get());

    return true;
}



DataCallbackResult
AudioEngine::onAudioReady(AudioStream *oboeStream, void *audioData, int32_t numFrames) {
    // If our audio stream is expecting 16-bit samples we need to render our floats into a separate
    // buffer then convert them into 16-bit ints
    bool is16Bit = (oboeStream->getFormat() == AudioFormat::I16);
    float *outputBuffer = (is16Bit) ? mConversionBuffer.get() : static_cast<float *>(audioData);

    for (int i = 0; i < numFrames; ++i) {

        mSongPositionMs = convertFramesToMillis(
                mCurrentFrame,
                mAudioStream->getSampleRate());

        mMixer.renderAudio(outputBuffer+(oboeStream->getChannelCount()*i), 1);
        mCurrentFrame++;
    }

    if (is16Bit){
        oboe::convertFloatToPcm16(outputBuffer,
                                  static_cast<int16_t*>(audioData),
                                  numFrames * oboeStream->getChannelCount());
    }

    mLastUpdateTime = nowUptimeMillis();

    return DataCallbackResult::Continue;
}

void AudioEngine::onErrorAfterClose(AudioStream *oboeStream, Result error) {
    AudioStreamCallback::onErrorAfterClose(oboeStream, error);
}


