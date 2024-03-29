/* This file is part of Clementine.
   Copyright 2010, David Sansome <me@davidsansome.com>

   Clementine is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   Clementine is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with Clementine.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef TRANSCODEDIALOG_H
#define TRANSCODEDIALOG_H

#include <QBasicTimer>
#include <QDialog>
#include <QFileInfo>
#include <memory>

class Transcoder;
class Ui_TranscodeDialog;
class Ui_TranscodeLogDialog;

struct TranscoderPreset;

class TranscodeDialog : public QDialog {
  Q_OBJECT

 public:
  TranscodeDialog(QWidget* parent = nullptr);
  ~TranscodeDialog();

  static const char* kSettingsGroup;
  static const int kProgressInterval;
  static const int kMaxDestinationItems;

  void SetFilenames(const QStringList& filenames);

 protected:
  void timerEvent(QTimerEvent* e);

 private slots:
  void Add();
  void Import();
  void Remove();
  void Start();
  void Cancel();
  void JobComplete(const QUrl& input, const QString& output, bool success);
  void LogLine(const QString& message);
  void AllJobsComplete();
  void Options();
  void AddDestination();
  void PipelineDumpAction(bool checked);

 private:
  void SetWorking(bool working);
  void UpdateStatusText();
  void UpdateProgress();
  QString GetOutputFileName(const QFileInfo& input,
                            const TranscoderPreset& preset) const;

 private:
  std::unique_ptr<Ui_TranscodeDialog> ui_;
  std::unique_ptr<Ui_TranscodeLogDialog> details_ui_;
  QDialog* details_dialog_;

  QBasicTimer progress_timer_;

  QPushButton* start_button_;
  QPushButton* cancel_button_;
  QPushButton* close_button_;

  QString last_add_dir_;
  QString last_import_dir_;

  Transcoder* transcoder_;
  int queued_;
  int finished_success_;
  int finished_failed_;
};

#endif  // TRANSCODEDIALOG_H
