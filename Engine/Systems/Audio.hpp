/*
** EPITECH PROJECT, 2022
** Project R-TYPE
** File description:
** Audio.hpp
*/

#ifndef AUDIO_HPP_
#define AUDIO_HPP_

#include <memory>
#include "ISound.hpp"

namespace PadaEngine {
    class Audio {
        public:
            Audio();
            ~Audio();
            void test();

        protected:
        private:
            std::shared_ptr<ISoundGame> _audio;
            std::unique_ptr<ISoundGame> _sound;
    };
}

#endif /* !AUDIO_HPP_ */
