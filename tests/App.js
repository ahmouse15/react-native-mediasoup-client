/**
 * Sample React Native App
 * https://github.com/facebook/react-native
 *
 * @format
 * @flow strict-local
 */

import React from 'react';
import type {Node} from 'react';
import {
  SafeAreaView,
  ScrollView,
  StatusBar,
  StyleSheet,
  Text,
  useColorScheme,
  View
} from 'react-native';

import {
  Colors,
  DebugInstructions,
  Header,
  LearnMoreLinks,
  ReloadInstructions,
} from 'react-native/Libraries/NewAppScreen';

import { NativeModules, NativeEventEmitter } from 'react-native';

//const MediasoupEventEmitter = new NativeEventEmitter(NativeModules.ReactNativeMediasoupClient);

var value;
var test = typeof NativeModules.ReactNativeMediasoupClient === "object";
NativeModules.ReactNativeMediasoupClient.test((res) => {
    value = res;
});

const Section = ({children, title}): Node => {
    const isDarkMode = useColorScheme() === 'dark';

  return (
    <View style={styles.sectionContainer}>
      <Text
        style={[
          styles.sectionTitle,
          {
            color: isDarkMode ? Colors.white : Colors.black,
          },
        ]}>
        {title}
      </Text>
      <Text
        style={[
          styles.sectionDescription,
          {
            color: isDarkMode ? Colors.light : Colors.dark,
          },
        ]}>
        {children}
      </Text>
    </View>
  );
};

const App: () => Node = () => {
  const isDarkMode = useColorScheme() === 'dark';

  const backgroundStyle = {
    backgroundColor: isDarkMode ? Colors.darker : Colors.lighter,
  };
 

  
    /*componentDidMount() {
        // Subscribing to MediasoupClient.AddEvent
        MediasoupEventEmitter.addListener('AddEvent', eventHandler, this);
    }

    componentWillUnmount() {
        // Unsubscribing from MediasoupClient.AddEvent
        MediasoupEventEmitter.removeListener('AddEvent', eventHandler, this);
    }

    eventHandler(result) {
        console.log("Event was fired with: " + result);
    }*/
	
  return (
	<SafeAreaView style={backgroundStyle}>
      <StatusBar barStyle={isDarkMode ? 'light-content' : 'dark-content'} />
      <ScrollView
        contentInsetAdjustmentBehavior="automatic"
        style={backgroundStyle}>
		<View
          style={{
            backgroundColor: isDarkMode ? Colors.black : Colors.white,
			color: isDarkMode ? Colors.white : Colors.black
          }}>
                  <Section>{(test && value == "ping") ? "All tests passed!" : "Test failed"}</Section>
		</View>
      </ScrollView>
    </SafeAreaView>);
};

const styles = StyleSheet.create({
  sectionContainer: {
    marginTop: 32,
    paddingHorizontal: 24,
  },
  sectionTitle: {
    fontSize: 24,
    fontWeight: '600',
  },
  sectionDescription: {
    marginTop: 8,
    fontSize: 18,
    fontWeight: '400',
  },
  highlight: {
    fontWeight: '700',
  },
});

export default App;
