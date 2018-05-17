#ifndef LAUNCHER_H
#define LAUNCHER_H

#include <memory>

#include <QComboBox>
#include <QDir>
#include <QHBoxLayout>
#include <QLabel>
#include <QMainWindow>
#include <QProcess>
#include <QPushButton>
#include <QVBoxLayout>

class Launcher : public QMainWindow
{
    Q_OBJECT

public:
    Launcher(QWidget* parent = nullptr);
    ~Launcher();

private:
    static const QString sViewerFile;

    static const QString sTrajectoriesPath;
    static const QString sSectionsPath;

    static const QFlags<Qt::AlignmentFlag> sCenterAlignment;

    /// Main layout.
    QWidget mMainWidget;
    QVBoxLayout mMainLayout;

    /// Attractors layout.
    QHBoxLayout mAttractorsLayout;

    /// First attractor layout.
    QVBoxLayout mFirstAttractorLayout;
    QLabel mFirstAttractorLabel;
    QHBoxLayout mFirstAttractorConfigLayout;
    QComboBox mFirstAttractorTrajectoryComboBox;
    QComboBox mFirstAttractorSectionComboBox;

    /// Second attractor layout.
    QVBoxLayout mSecondAttractorLayout;
    QLabel mSecondAttractorLabel;
    QHBoxLayout mSecondAttractorConfigLayout;
    QComboBox mSecondAttractorTrajectoryComboBox;
    QComboBox mSecondAttractorSectionComboBox;

    /// Controls layout.
    QHBoxLayout mControlsLayout;
    QPushButton mRunButton;

    std::unique_ptr<QProcess> mViewerProcess;

    void configureWindow();
    void generateComboBox(QComboBox* comboBox, QString res);

    void runViewer();
};

#endif // LAUNCHER_H
