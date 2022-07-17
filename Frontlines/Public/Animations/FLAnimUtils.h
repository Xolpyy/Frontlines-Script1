#pragma once

class UAnimSequenceBase;

class FLAnimUtils
{
public:
    template <typename T>
    static T *FindNotifyByClass(UAnimSequenceBase *Animation)
    {
        if (!Animation)
            return nullptr;

        const auto Notifies = Animation->Notifies;
        for (const auto AnimNotify : Notifies)
        {
            const auto Notify = Cast<T>(AnimNotify.Notify);
            if (Notify)
            {
                return Notify;
            }
        }

        return nullptr;
    }
};