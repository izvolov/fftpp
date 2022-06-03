#pragma once

namespace fftpp
{
    /*!
        \~english
            \brief
                A structure.

            \details
                Just a demo of documentation.

        \~russian
            \brief
                Структура.

            \details
                Для демонстрации автодокументирования.

        \~  \see myfunc
     */
    struct mystruct
    {
    };

    /*!
        \~english
            \brief
                A function

            \details
                Does nothing.

            \returns
                True.

        \~russian
            \brief
                Функция

            \details
                Ничего не делает.

            \returns
                Истину.

        \~  \see mystruct
     */
    bool myfunc (mystruct);
}
