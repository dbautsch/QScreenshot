#ifndef PASSWORDSSHELTER_H
#define PASSWORDSSHELTER_H


class PasswordsShelter
{
public:
    PasswordsShelter();

    bool    GetLoginPasswordForService(const QString    & strServiceName,
                                       QString          & strLogin,
                                       QString          & strPassword);

    void    SetLoginPasswordForService(const QString    & strServiceName,
                                       const QString    & strLogin,
                                       const QString    & strPassword);
};

#endif // PASSWORDSSHELTER_H
