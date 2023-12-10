import librosa
import soundfile as sf

def resample_wav(input_file, output_file, target_sr):
    # Load the audio file
    audio, sr = librosa.load(input_file, sr=None)

    # Resample the audio
    audio_resampled = librosa.resample(audio, orig_sr=sr, target_sr=target_sr)

    # Save the resampled audio file
    sf.write(output_file, audio_resampled, target_sr)

# Input file name
input_file = 'good_mixed_output.wav'  # Replace with your input file name

# User inputs new sampling rate
target_sr = int(input("Please enter the new sampling rate (e.g., 44100): "))

# Output file name
output_file = 'output_resampled.wav'  # Output file name

resample_wav(input_file, output_file, target_sr)
