# Naïve Bayes Instrument Classification Proposal

## Premise:
My idea for this project is to take the simple Naïve Bayes classifier we made for handwritten digits and extend it to classify something more complicated, specifically audio. I want to create and train a model using some collected dataset of audio files. After brainstorming what type of audio could be good to use for this project (i.e. vocal accents, emotion in speaking, songs, etc.), I decided that analyzing audio files of individual instruments could yield accurate results from the classifier due to the various unique timbres of different instruments. 
## Dataset:
[minst-dataset](https://github.com/ejhumphrey/minst-dataset)
I found this dataset called minst (play on MNIST) which holds a collection of several datasets containing audio files of individual instruments being played. This dataset was compiled with the intention of machine learning in mind. This is perfect for my project as this should be sufficient to both train and test the classifier.
## Features:
There are many options for feature extraction of an audio file, some more useful than others. I plan on at least extracting the MFCC, energy, and zero-crossing rate of each training file and finding their means, medians, standard deviations, and extrema. The mel-frequency cepstral coefficient (MFCC) adjusts a given frequency to a more human-friendly scale and thus serves as a great identifying feature of a specific audio type. The energy of the audio describes the distribution of amplitude into the frequency components of that signal. This may be calculated by iterating over each bin of the audio’s Fourier transformation. The zero-crossing rate (ZCR) is simply the rate at which the signal changes sign in terms of amplitude. This gives a general indication of the “noisiness” of a signal and is commonly used for audio classification.
## Bayes:
To calculate the needed probabilities for Naïve Bayes, I will be able to approach this problem in a similar manner to the digit classification assignment. However, there are continuous numerical values for which I will need to discretize. With digit classification, there were only two values any given feature could have. When analyzing audio, the ZCR for example could be any range of real numbers within some domain. Because of this, calculating the simple probability of a feature being equal to a specific ZCR for a certain class will not produce a desirable result. To compensate for this, I will create subjective ranges of values to limit the potential values of each features to create a reasonable training model. 
## Libraries:
[Maxmilian](https://github.com/micknoise/Maximilian)
In addition to openframeworks GUI and Sound libraries, the main external library I will use is called Maximilian. This is a C++ digital signal processing library that contains an abundance of methods for spectral analysis and running calculations on audio samples. It has many different Fourier transformation methods, including the discrete cosine transform which is important for retrieving the MFCC.
## Information Sources:
These sources are very informative and provided the inspiration for this project.
[Emotion recognition of the basis of audio signal using Naïve Bayes classifier](https://ieeexplore.ieee.org/abstract/document/7732408/authors#authors)
[Multi-Label Feature Selection With Application to Musical Instrument Recognition](https://pdfs.semanticscholar.org/b70e/c995318f6f967f777183f4f76aff8ee8b5ac.pdf)
